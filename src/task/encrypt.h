//
// Created by J Chen on 2023/11/22.
//

#ifndef SRC_TASK_ENCRYPT_H_
#define SRC_TASK_ENCRYPT_H_

#include "autumn/log.h"
#include "src/log_def.h"
#include "src/task.h"

namespace autumn {

class EncryptTask : public BaseTask<LogEntry, LogEntry> {
 public:
  explicit EncryptTask(const LogConfig& config) : BaseTask() {}
  ~EncryptTask() override = default;

  void Run(const LogEntry& in) override;
  void Finish(const LogEntry& out) override;
};

}  // namespace autumn

#endif  // SRC_TASK_ENCRYPT_H_
