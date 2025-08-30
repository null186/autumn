//
// Created by J Chen on 2023/12/31.
//

#include "file.h"

#include <dirent.h>
#include <sys/stat.h>

#include <cassert>
#include <regex>

namespace autumn {

static const std::string kPrefix = "autumn-";
static const std::string kExtension = ".log";

void LogFile::Open() { fp_ = fopen(path_.c_str(), "ab+"); }

void LogFile::Close() {
  if (!fp_) {
    return;
  }

  fclose(fp_);
  fp_ = nullptr;
}

void LogFile::Remove() { std::remove(path_.c_str()); }

std::time_t LogFile::ModifyTime() const { return mtime_; }

size_t LogFile::Index() const { return index_; }

bool LogFile::CanWrite(size_t size) const {
  return size_ + size <= max_file_size_;
}

size_t LogFile::Write(const std::string& data) {
  size_t written = fwrite(data.c_str(), sizeof(char), data.size(), fp_);
  size_ += written;
  if (written == data.size()) {
    fflush(fp_);
  }
  return written;
}

LogDir::LogDir(size_t max_files, size_t max_file_size, std::string dir_path)
    : max_files_(max_files),
      max_file_size_(max_file_size),
      dir_path_(std::move(dir_path)) {
  Init();
}

LogDir::~LogDir() {
  if (!list_.empty()) {
    list_.back()->Close();
  }
  for (auto item : list_) {
    assert(item);
    delete item;
  }
}

void LogDir::Init() {
  DIR* dir = opendir(dir_path_.c_str());
  if (dir == nullptr) {
    return;
  }

  struct dirent* d;
  struct stat s{};
  std::string content;
  content.append(kPrefix).append("(\\d+)").append(kExtension);
  const std::regex regex(content);
  while ((d = readdir(dir)) != nullptr) {
    std::string filename = d->d_name;
    std::smatch match;
    if (!std::regex_match(filename, match, regex)) {
      continue;
    }
    std::string index = match.str(1);
    if (index.empty()) {
      continue;
    }
    std::string path = dir_path_ + "/" + filename;
    if (stat(path.c_str(), &s) != 0) {
      continue;
    }
    list_.push_back(new LogFile(max_file_size_, std::stoi(index), path,
                                s.st_mtime, s.st_size));
  }

  assert(list_.size() <= max_files_);
  if (list_.empty()) {
    return;
  }

  list_.sort([](const LogFile* a, const LogFile* b) {
    assert(a && b);
    return a->ModifyTime() < b->ModifyTime();
  });
  list_.back()->Open();
}

LogFile* LogDir::GetLogFile(size_t size) {
  if (!list_.empty() && list_.back()->CanWrite(size)) {
    return list_.back();
  }

  RollFile();

  return list_.back();
}

void LogDir::RollFile() {
  size_t index = 0;
  if (!list_.empty()) {
    index = (list_.back()->Index() + 1) % max_files_;
    list_.back()->Close();
  }
  std::string path = kPrefix + std::to_string(index) + kExtension;
  auto new_file = new LogFile(max_file_size_, index, path);
  list_.push_back(new_file);

  if (list_.size() > max_files_) {
    size_t oversize = list_.size() - max_files_;
    for (size_t i = 0; i < oversize; ++i) {
      auto* oldest_file = list_.front();
      oldest_file->Remove();
      delete oldest_file;
      list_.pop_front();
    }
  }
  list_.back()->Open();
}

FileWriter::FileWriter(size_t max_files, size_t max_file_size,
                       std::string dir_path) {
  log_dir_ = new LogDir(max_files, max_file_size, std::move(dir_path));
}

FileWriter::~FileWriter() {
  delete log_dir_;
  log_dir_ = nullptr;
}

uint64_t FileWriter::Write(const std::string& data) {
  std::lock_guard<std::mutex> lock_guard(mutex_);
  if (!log_dir_) {
    return 0;
  }
  auto* log_file = log_dir_->GetLogFile(data.size());
  return log_file->Write(data);
}

}  // namespace autumn
