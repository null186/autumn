//
// Created by J Chen on 2023/12/2.
//

#pragma once

#include <vector>

#include "logger.h"
#include "task.h"

namespace autumn {

class FormatTask;
class CompressTask;
class EncryptTask;
class StreamTask;
class WriteTask;

class AssemblerTask : public BaseTask<LogMessage, LogMessage> {
 public:
  explicit AssemblerTask(const LogConfig& config);
  ~AssemblerTask() override;

 public:
  void Assembler();

 public:
  void Run() override;
  void Finish(const LogMessage& param) override;

 private:
  FormatTask* format_task_ = nullptr;
  CompressTask* compress_task_ = nullptr;
  EncryptTask* encrypt_task_ = nullptr;
  StreamTask* stream_task_ = nullptr;
  WriteTask* write_task_ = nullptr;
};

}  // namespace autumn
