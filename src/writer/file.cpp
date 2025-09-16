//
// Created by J Chen on 2023/12/31.
//

#include "src/writer/file.h"

#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cassert>
#include <regex>
#include <sstream>

#include "src/utils/inner_log.h"

namespace autumn {

static constexpr char kPrefix[] = "autumn-";
static constexpr char kExtension[] = ".log";

bool MmapFile::Open() {
  static constexpr int kMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
  fd_ = open(path().c_str(), O_RDWR | O_CREAT, kMode);
  if (fd_ == -1) {
    return false;
  }

  struct stat st;
  if (fstat(fd_, &st) == -1) {
    Reset();
    return false;
  }
  assert(st.st_size >= 0 && st.st_size <= static_cast<off_t>(max_size()));
  size_ = st.st_size;

  if (ftruncate(fd_, static_cast<off_t>(max_size())) == -1) {
    Reset();
    return false;
  }

  static constexpr int kProt = PROT_READ | PROT_WRITE;
  void* data = mmap(nullptr, max_size(), kProt, MAP_SHARED, fd_, 0);
  if (!data) {
    Reset();
    return false;
  }

  data_ = static_cast<char*>(data);
  return true;
}

void MmapFile::Close() { Reset(); }

void MmapFile::Remove() {
  if (data_ != nullptr) {
    munmap(data_, max_size());
    data_ = nullptr;
  }

  if (fd_ != -1) {
    close(fd_);
    fd_ = -1;
  }

  std::remove(path().c_str());
}

bool MmapFile::CanWrite(size_t size) const {
  return size_ + size <= max_size();
}
size_t MmapFile::Write(const std::string& data) {
  if (!data_) {
    return 0;
  }
  std::copy(data.begin(), data.end(), data_ + size_);
  size_ += data.size();
  return data.size();
}

size_t MmapFile::Write(const std::vector<char>& data) {
  if (!data_) {
    return 0;
  }
  std::copy(data.begin(), data.end(), data_ + size_);
  size_ += data.size();
  return data.size();
}

void MmapFile::Reset() {
  if (data_ != nullptr) {
    msync(data_, size_, MS_SYNC);
    munmap(data_, max_size());
    data_ = nullptr;
  }

  if (fd_ != -1) {
    ftruncate(fd_, static_cast<off_t>(size_));
    close(fd_);
    fd_ = -1;
  }
}

bool Normalile::Open() {
  fp_ = fopen(path().c_str(), "ab+");
  return fp_ != nullptr;
}

void Normalile::Close() {
  if (!fp_) {
    return;
  }

  fclose(fp_);
  fp_ = nullptr;
}

void Normalile::Remove() { std::remove(path().c_str()); }

bool Normalile::CanWrite(size_t size) const {
  return size_ + size <= max_size();
}

size_t Normalile::Write(const std::string& data) {
  const size_t written = fwrite(data.c_str(), sizeof(char), data.size(), fp_);
  size_ += written;
  if (written == data.size()) {
    fflush(fp_);
  }
  return written;
}

size_t Normalile::Write(const std::vector<char>& data) {
  const size_t written = fwrite(data.data(), sizeof(char), data.size(), fp_);
  size_ += written;
  if (written == data.size()) {
    fflush(fp_);
  }
  return written;
}

LogDir::LogDir(size_t max_files, size_t max_file_size, fs::path dir_path)
    : max_files_(max_files),
      max_file_size_(max_file_size),
      dir_path_(std::move(dir_path)) {}

LogDir::~LogDir() {
  if (!list_.empty()) {
    list_.back()->Close();
  }
}

void LogDir::Init() {
  std::error_code ec;
  auto dir_status = fs::status(dir_path_, ec);
  if (ec) {
    ilog << "error getting " << dir_path_ << " status: " << ec.message()
         << end_line;
    return;
  }

  if (fs::is_directory(dir_status)) {
    ilog << dir_path_ << "is not a dir" << end_line;
  }

  std::string content;
  content.append(kPrefix).append("(\\d+)").append(kExtension);
  const std::regex regex(content);
  for (const auto& entry : fs::directory_iterator(dir_path_, ec)) {
    if (ec) {
      ilog << "error getting " << dir_path_ << " entry: " << ec.message()
           << end_line;
      break;
    }

    const fs::path& path = entry.path();
    auto file_status = fs::status(path, ec);
    if (ec) {
      ilog << "error getting " << path << " status: " << ec.message()
           << end_line;
      continue;
    }
    if (!entry.is_regular_file()) {
      ilog << path << " is not a regular file: " << end_line;
      continue;
    }

    const std::string& filename = path.filename().string();
    std::smatch match;
    if (!std::regex_match(filename, match, regex)) {
      continue;
    }
    if (match.str(1).empty()) {
      continue;
    }
    const auto index = static_cast<size_t>(std::stoi(match.str(1)));
    const auto mtime = fs::last_write_time(path);
    auto size = fs::file_size(path);
    LogFile::Meta meta{index, max_file_size_, mtime, path};
    auto new_file = std::make_unique<Normalile>(meta, size);
    list_.push_back(std::move(new_file));
  }

  assert(list_.size() <= max_files_);
  if (list_.empty()) {
    return;
  }

  list_.sort(
      [](const std::unique_ptr<LogFile>& a, const std::unique_ptr<LogFile>& b) {
        return a->mtime() < b->mtime();
      });
  list_.back()->Open();
}

LogFile* LogDir::GetLogFile(size_t size) {
  if (!list_.empty() && list_.back()->CanWrite(size)) {
    return list_.back().get();
  }

  RollFile();

  return list_.back().get();
}

fs::path LogDir::GenPath(const size_t index) const {
  if (!fs::exists(dir_path_)) {
    fs::create_directories(dir_path_);
  }
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(log10(max_files_) + 1) << (index);
  std::string filename;
  filename.append(kPrefix).append(ss.str()).append(kExtension);
  return dir_path_ / filename;
}

void LogDir::RollFile() {
  size_t index = 0;
  if (!list_.empty()) {
    index = (list_.back()->index() + 1) % max_files_;
    list_.back()->Close();
  }

  LogFile::Meta meta{index, max_file_size_, {}, GenPath(index)};
  auto new_file = std::make_unique<Normalile>(meta, 0);
  list_.push_back(std::move(new_file));

  if (list_.size() > max_files_) {
    size_t oversize = list_.size() - max_files_;
    for (size_t i = 0; i < oversize; ++i) {
      auto* oldest_file = list_.front().get();
      oldest_file->Remove();
      list_.pop_front();
    }
  }
  list_.back()->Open();
}

FileWriter::FileWriter(size_t max_files, size_t max_file_size,
                       std::string dir_path)
    : log_dir_(std::make_unique<LogDir>(max_files, max_file_size,
                                        std::move(dir_path))) {
  log_dir_->Init();
}

uint64_t FileWriter::Write(const std::string& data) {
  std::lock_guard lock_guard(mutex_);
  if (!log_dir_) {
    return 0;
  }
  auto* log_file = log_dir_->GetLogFile(data.size());
  return log_file->Write(data);
}

}  // namespace autumn
