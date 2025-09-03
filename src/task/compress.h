//
// Created by J Chen on 2023/11/22.
//

#ifndef SRC_TASK_COMPRESS_H_
#define SRC_TASK_COMPRESS_H_

#include <string>

#include "autumn/log.h"
#include "log_def.h"
#include "task.h"

namespace autumn {

class CompressTask : public BaseTask<LogEntry, LogEntry> {
 public:
  explicit CompressTask(const LogConfig& config)
      : BaseTask<LogEntry, LogEntry>() {}
  ~CompressTask() override = default;

 public:
  void Run() override;
  void Finish(const LogEntry& param) override;
};

}  // namespace autumn

#endif  // SRC_TASK_COMPRESS_H_
