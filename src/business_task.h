//
// Created by J Chen on 2023/11/27.
//

#pragma once

#include <iostream>

#include "base_task.h"

namespace autumn {

template <typename I, typename O>
class BusinessTask : public BaseTask<I, O> {
  public:
    explicit BusinessTask(TaskContext* tc) : BaseTask<I, O>(tc) {}
    ~BusinessTask() override = default;

  public:
    void TaskSuccess(O* param) override { BaseTask<I, O>::TaskSuccess(param); }
    void TaskFailed() override { BaseTask<I, O>::TaskFailed(); }
};

}  // namespace autumn
