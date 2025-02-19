//
// Created by J Chen on 2023/12/2.
//

#pragma once

#include <vector>

#include "base_task.h"
#include "logger.h"

namespace autumn {

class FormatTask;
class CompressTask;
class EncryptTask;
class StreamTask;
class WriteTask;

class AssemblerTask : public BaseTask<Message, Message> {
  public:
    explicit AssemblerTask(TaskContext* tc);
    ~AssemblerTask() override;

  public:
    void Assembler();

  public:
    void SetParam(Message param) override;
    void Start() override;
    void Finish() override;

  private:
    TaskContext* task_context_ = nullptr;

  private:
    FormatTask* format_task_ = nullptr;
    CompressTask* compress_task_ = nullptr;
    EncryptTask* encrypt_task_ = nullptr;
    StreamTask* stream_task_ = nullptr;
    WriteTask* write_task_ = nullptr;
};

}  // namespace autumn
