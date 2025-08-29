//
// Created by J Chen on 2023/12/2.
//

#include "assembler.h"

#include "logger.h"
#include "task/compress_task.h"
#include "task/encrypt_task.h"
#include "task/format_task.h"
#include "task/stream_task.h"
#include "task/write_task.h"

namespace autumn {

AssemblerTask::AssemblerTask(const LogConfig& config)
    : BaseTask<LogMessage, LogMessage>() {
  format_task_ = new FormatTask(config);
  compress_task_ = new CompressTask(config);
  encrypt_task_ = new EncryptTask(config);
  stream_task_ = new StreamTask(config);
  write_task_ = new WriteTask(config);
}

AssemblerTask::~AssemblerTask() {
  delete format_task_;
  delete compress_task_;
  delete encrypt_task_;
  delete stream_task_;
  delete write_task_;
}

void AssemblerTask::Assembler() {
  BaseTask<LogMessage, LogMessage>::Then(format_task_)
      ->Then(compress_task_)
      ->Then(encrypt_task_)
      ->Then(write_task_)
      ->Follow(stream_task_);
}

void AssemblerTask::Run() {
  // TODO: 详细校验 LogMessage 有效性。
  if (params_.message.empty()) {
    BaseTask<LogMessage, LogMessage>::Failed(
        BaseTask<LogMessage, LogMessage>::params_);
  } else {
    BaseTask<LogMessage, LogMessage>::Success(
        BaseTask<LogMessage, LogMessage>::params_);
  }
}

void AssemblerTask::Finish(const LogMessage& param) {
  // TODO: 待实现
}

}  // namespace autumn
