//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include <string>

#include "task.h"
#include "logger.h"
#include "autumn/config.h"

namespace autumn {

class EncryptTask : public BaseTask<LogEntry, LogEntry> {
 public:
  explicit EncryptTask(const LogConfig& config)
      : BaseTask<LogEntry, LogEntry>() {}
  ~EncryptTask() override = default;

 public:
  void Run() override;
  void Finish(const LogEntry& param) override;
};

}  // namespace autumn
