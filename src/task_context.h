//
// Created by J Chen on 2023/11/25.
//

#pragma once

#include <utility>

#include "autumn/config.h"

namespace autumn {

class TaskContext {
  public:
    explicit TaskContext(LogConfig log_config) : log_config_(std::move(log_config)) {}
    ~TaskContext() = default;

  public:
    const std::string& GetWorkDir() const { return log_config_.work_dir; }
    size_t GetMaxFiles() const { return log_config_.max_files; }
    size_t GetMaxFileSize() const { return log_config_.max_file_size; }
    LogType GetTypeMask() const { return log_config_.type_mask; }
    LogPriority GetPriority() const { return log_config_.priority; }

  private:
    const LogConfig log_config_;
};

}  // namespace autumn
