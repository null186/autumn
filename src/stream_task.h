//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "business_task.h"
namespace autumn {

class StreamTask : public BusinessTask<std::string, std::string> {
  public:
    explicit StreamTask(TaskContext* tc) : BusinessTask<std::string, std::string>(tc) {}
    ~StreamTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};
}  // namespace autumn
