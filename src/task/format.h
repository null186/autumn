//
// Created by J Chen on 2023/12/17.
//

#ifndef SRC_TASK_FORMAT_H_
#define SRC_TASK_FORMAT_H_

#include "autumn/config.h"
#include "logger.h"
#include "task.h"

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

#endif  // SRC_TASK_FORMAT_H_
