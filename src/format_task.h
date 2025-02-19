//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "business_task.h"
#include "logger.h"

namespace autumn {

struct LogMessage;

class FormatTask : public BusinessTask<LogMessage, LogEntry> {
  public:
    explicit FormatTask(TaskContext* tc) : BusinessTask<LogMessage, LogEntry>(tc) {}
    ~FormatTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn