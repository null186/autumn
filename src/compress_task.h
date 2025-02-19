//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include <string>

#include "business_task.h"

namespace autumn {

class CompressTask : public BusinessTask<int, bool> {
  public:
    explicit CompressTask(TaskContext* tc) : BusinessTask<int, bool>(tc) {}
    ~CompressTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn
