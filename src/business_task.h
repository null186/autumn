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
    explicit BusinessTask(TaskContext* tc);

  protected:
    ~BusinessTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn
