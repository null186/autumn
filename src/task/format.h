//
// Created by J Chen on 2023/12/17.
//

#ifndef SRC_TASK_FORMAT_H_
#define SRC_TASK_FORMAT_H_

#include "autumn/log.h"
#include "src/log_def.h"
#include "src/task.h"

namespace autumn {

struct LogMessage;

class FormatTask : public BaseTask<LogMessage, LogEntry> {
 public:
  explicit FormatTask(const LogConfig& config) : BaseTask() {}
  ~FormatTask() override = default;

  void Run(const LogMessage& in) override;
  void Finish(const LogEntry& out) override;
};

}  // namespace autumn

#endif  // SRC_TASK_FORMAT_H_
