//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "task.h"
#include "logger.h"
#include "autumn/config.h"

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