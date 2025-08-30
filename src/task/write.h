//
// Created by J Chen on 2023/12/17.
//

#ifndef SRC_TASK_WRITE_H_
#define SRC_TASK_WRITE_H_

#include "autumn/config.h"
#include "logger.h"
#include "task.h"

namespace autumn {

class FileWriter;

class WriteTask : public BaseTask<LogEntry, std::string> {
 public:
  explicit WriteTask(const LogConfig& config);
  ~WriteTask() override;

 public:
  void Run() override;
  void Finish(const std::string& param) override;

 private:
  FileWriter* file_writer_ = nullptr;
};

}  // namespace autumn

#endif  // SRC_TASK_WRITE_H_
