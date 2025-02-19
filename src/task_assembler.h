//
// Created by J Chen on 2023/12/2.
//

#pragma once

#include <vector>

#include "base_task.h"

namespace autumn {

class EncryptTask;
class CompressTask;

class TaskAssembler : public BaseTask<void, void> {
  public:
    explicit TaskAssembler(TaskContext* tc);
    ~TaskAssembler() override;

  public:
    void Assembler();

  public:
    void SetParam(void* param) override;
    void Start() override;
    void Finish() override;

  private:
    TaskContext* task_context_ = nullptr;

  private:
    EncryptTask* encrypt_task_ = nullptr;
    CompressTask* compress_task_ = nullptr;
};

}  // namespace autumn
