//
// Created by J Chen on 2023/12/31.
//

#include "log_files.h"

#include <dirent.h>
#include <sys/stat.h>

#include <regex>

namespace autumn {

static const std::string kPrefix = "autumn-";
static const std::string kExtension = ".log";

void LogFile::Open() {
    fp_ = fopen(path_.c_str(), "ab+");
}

void LogFile::Close() {
    if (!fp_) {
        return;
    }

    fclose(fp_);
    fp_ = nullptr;
}

void LogFile::Remove() {
    std::remove(path_.c_str());
}

std::time_t LogFile::ModifyTime() const {
    return mtime_;
}

size_t LogFile::Index() const {
    return index_;
}

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
    : max_files_(max_files), max_file_size_(max_file_size), dir_path_(std::move(dir_path)) {
    Init();
}

LogDir::~LogDir() {
    for (auto item : list_) {
        if (!item) {
            break;
        }

        item->Close();
        delete item;
    }
}

void LogDir::Init() {
    DIR* dir = opendir(dir_path_.c_str());
    if (dir == nullptr) {
        return;
    }

    struct dirent* d;
    struct stat s {};
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
        list_.push_back(new LogFile(max_file_size_, std::stoi(index), path, s.st_mtime, s.st_size));
    }

    if (list_.empty()) {
        return;
    }

    list_.sort([](LogFile* a, LogFile* b) { return a->ModifyTime() < b->ModifyTime(); });
    list_.back()->Open();
    assert(list_.size() <= max_files_);
}

LogFile* LogDir::GetLogFile(size_t size) {
    if (!list_.empty() && list_.back()->CanWrite(size)) {
        return list_.back();
    }

    RollFile();

    return list_.back();
}

void LogDir::RollFile() {
    size_t index = list_.back()->Index();
    if (++index >= max_files_) {
        index = 0;
    }
    std::string path = kPrefix + std::to_string(index) + kExtension;
    auto log_file = new LogFile(max_file_size_, index, path);
    list_.back()->Close();
    log_file->Open();
    list_.push_back(log_file);

    if (list_.size() <= max_files_) {
        return;
    }

    size_t oversize = list_.size() - max_files_;
    for (size_t i = 0; i <= oversize; ++i) {
        list_.front()->Remove();
        list_.pop_front();
    }
}

}  // namespace autumn
