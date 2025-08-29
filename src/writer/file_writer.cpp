//
// Created by J Chen on 2023/12/31.
//

#include "file_writer.h"

namespace autumn {

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
