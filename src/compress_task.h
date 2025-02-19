//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include <string>

#include "business_task.h"

namespace autumn {

class CompressTask : public BusinessTask<std::string, std::string> {
  public:
    explicit CompressTask(TaskContext* tc) : BusinessTask<std::string, std::string>(tc) {}
    ~CompressTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn
