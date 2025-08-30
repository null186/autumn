//
// Created by J Chen on 2023/11/22.
//

#ifndef SRC_TASK_ENCRYPT_H_
#define SRC_TASK_ENCRYPT_H_

#include <string>

#include "autumn/config.h"
#include "logger.h"
#include "task.h"

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

#endif  // SRC_TASK_ENCRYPT_H_
