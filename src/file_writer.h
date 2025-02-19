//
// Created by J Chen on 2023/12/31.
//

#pragma once

#include <cstdint>

#include "file_queue.h"

namespace autumn {

class FileWriter {
  public:
    FileWriter(size_t max_files, size_t max_file_size, std::string dir_path);
    ~FileWriter();

  public:
    uint64_t Write(const std::string& data);

  private:
    std::time_t ModifyTime();
    std::string GetNextFileName();
    void OpenNewFile();
    bool OpenOldFile();

  private:
    const size_t max_files_;
    const size_t max_file_size_;
    const std::string dir_path_;
    FileQueue* file_queue_ = nullptr;
    FILE* fp_ = nullptr;
    std::string file_path_;
    size_t size_ = 0;
    size_t index_ = 0;
};

}  // namespace autumn
