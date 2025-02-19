//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "business_task.h"
#include "logger.h"

namespace autumn {

struct Message;

class FormatTask : public BusinessTask<Message, std::string> {
  public:
    explicit FormatTask(TaskContext* tc) : BusinessTask(tc) {}
    ~FormatTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn