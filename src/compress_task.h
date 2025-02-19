//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include <string>

#include "business_task.h"

namespace autumn {

class CompressTask : public BusinessTask<LogEntry, LogEntry> {
  public:
    explicit CompressTask(TaskContext* tc) : BusinessTask<LogEntry, LogEntry>(tc) {}
    ~CompressTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn
