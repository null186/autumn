//
// Created by J Chen on 2023/11/27.
//

#pragma once

#include <iostream>

#include "base_task.h"

namespace autumn {

struct LogEntry {
    /** The log type name. */
    char type[16] = {};
    /** The log entry itself. */
    std::string entry{};
};

template <typename I, typename O>
class BusinessTask : public BaseTask<I, O> {
  public:
    explicit BusinessTask(TaskContext* tc) : BaseTask<I, O>(tc) {}
    ~BusinessTask() override = default;

  public:
    void TaskSuccess(const O& param) override { BaseTask<I, O>::TaskSuccess(param); }
    void TaskFailed(const O& param) override { BaseTask<I, O>::TaskFailed(param); }
};

}  // namespace autumn
