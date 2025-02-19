//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "business_task.h"

namespace autumn {

class WriteTask : public BusinessTask<LogEntry, std::string> {
  public:
    explicit WriteTask(TaskContext* tc) : BusinessTask<LogEntry, std::string>(tc) {}
    ~WriteTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn