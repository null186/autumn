//
// Created by J Chen on 2023/11/22.
//

#ifndef SRC_TASK_COMPRESS_H_
#define SRC_TASK_COMPRESS_H_

#include "autumn/log.h"
#include "src/log_def.h"
#include "src/task.h"

namespace autumn {

class CompressTask : public BaseTask<LogEntry, LogEntry> {
 public:
  explicit CompressTask(const LogConfig& config) : BaseTask() {}
  ~CompressTask() override = default;

  void Run(const LogEntry& in) override;
  void Finish(const LogEntry& out) override;
};

}  // namespace autumn

#endif  // SRC_TASK_COMPRESS_H_
