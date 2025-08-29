//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "task.h"
#include "logger.h"
#include "autumn/config.h"

namespace autumn {

struct LogMessage;

class FormatTask : public BaseTask<LogMessage, LogEntry> {
 public:
  explicit FormatTask(const LogConfig& config)
      : BaseTask<LogMessage, LogEntry>() {}
  ~FormatTask() override = default;

 public:
  void Run() override;
  void Finish(const LogEntry& param) override;
};

}  // namespace autumn