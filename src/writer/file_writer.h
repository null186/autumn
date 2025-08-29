//
// Created by J Chen on 2023/12/31.
//

#pragma once

#include <cstdint>
#include <mutex>

#include "log_files.h"

namespace autumn {

class FileWriter {
 public:
  FileWriter(size_t max_files, size_t max_file_size, std::string dir_path);
  ~FileWriter();

 public:
  uint64_t Write(const std::string& data);

 private:
  std::mutex mutex_;
  LogDir* log_dir_ = nullptr;
};

}  // namespace autumn
