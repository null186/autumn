//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include <string>

#include "business_task.h"

namespace autumn {

class EncryptTask : public BusinessTask<std::string, std::string> {
  public:
    explicit EncryptTask(TaskContext* tc);
    ~EncryptTask() override;

  public:
    void Start() override;
};

}  // namespace autumn
