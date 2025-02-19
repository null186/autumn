//
// Created by J Chen on 2023/12/31.
//

#pragma once

#include <list>
#include <string>
#include <utility>

namespace autumn {

class FileInfo {
  public:
    FileInfo() = default;
    FileInfo(size_t size, size_t index, time_t mtime, std::string path)
        : size(size), index(index), mtime(mtime), path(std::move(path)) {}
    ~FileInfo() = default;

  public:
    static const std::string prefix;
    static const std::string extension;
    size_t size = 0;
    size_t index = 0;
    std::time_t mtime = 0;
    std::string path;
};

class FileQueue {
  public:
    FileQueue(size_t max_files, size_t max_file_size, std::string dir_path);
    ~FileQueue() = default;

  public:
    void Init();
    bool PopBack(FileInfo& out_info);
    void Enqueue(const FileInfo& file_info);

  private:
    void AutoRemoveIfNeed();

  private:
    const size_t max_files_;
    const size_t max_file_size_;
    const std::string dir_path_;
    std::list<FileInfo> list_;
};

}  // namespace autumn
