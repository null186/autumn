//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include <string>

#include "business_task.h"

namespace autumn {

class EncryptTask : public BusinessTask<void, int> {
  public:
    explicit EncryptTask(TaskContext* tc) : BusinessTask<void, int>(tc) {}
    ~EncryptTask() override = default;

  public:
    void Start() override;
    void Finish() override;
};

}  // namespace autumn
