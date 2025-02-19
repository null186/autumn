//
// Created by J Chen on 2023/12/31.
//

#include "file_queue.h"

#include <dirent.h>
#include <sys/stat.h>

#include <regex>

namespace autumn {

const std::string FileInfo::prefix = "autumn-";
const std::string FileInfo::extension = ".log";

FileQueue::FileQueue(size_t max_files, size_t max_file_size, std::string dir_path)
    : max_files_(max_files), max_file_size_(max_file_size), dir_path_(std::move(dir_path)) {
    Init();
}

void FileQueue::Init() {
    DIR* dir = opendir(dir_path_.c_str());
    if (dir == nullptr) {
        return;
    }

    struct dirent* d;
    struct stat s {};

    while ((d = readdir(dir)) != nullptr) {
        std::string filename = d->d_name;
        std::string content;
        content.append(FileInfo::prefix).append("(\\d+)").append(FileInfo::extension);
        const std::regex regex(content);
        std::smatch match;
        if (!std::regex_match(filename, match, regex)) {
            continue;
        }
        std::string index = match.str(1);
        if (index.empty()) {
            continue;
        }
        std::string file_path = dir_path_ + "/" + filename;
        if (stat(file_path.c_str(), &s) != 0) {
            continue;
        }
        list_.emplace_back(static_cast<size_t>(s.st_size), std::stoi(index), s.st_mtime, filename);
    }

    list_.sort([](const FileInfo& a, const FileInfo& b) { return a.mtime < b.mtime; });
    assert(list_.size() <= max_files_);
}

bool FileQueue::PopBack(FileInfo& out_info) {
    if (list_.empty()) {
        return false;
    }

    out_info = list_.back();
    list_.pop_back();
    return true;
}

void FileQueue::Enqueue(const FileInfo& file_info) {
    list_.emplace_back(file_info);
    AutoRemoveIfNeed();
}

void FileQueue::AutoRemoveIfNeed() {
    if (list_.size() < max_files_) {
        return;
    }

    size_t oversize = list_.size() - max_files_;
    for (size_t i = 0; i <= oversize; ++i) {
        auto& file_info = list_.front();
        std::remove(file_info.path.c_str());
        list_.pop_front();
    }
}

}  // namespace autumn
