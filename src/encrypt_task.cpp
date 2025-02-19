//
// Created by J Chen on 2023/11/22.
//

#include "encrypt_task.h"

namespace autumn {

EncryptTask::EncryptTask(TaskContext* tc) : BusinessTask<std::string, std::string>(tc) {}

EncryptTask::~EncryptTask() = default;

void EncryptTask::Start() {
    BaseTask<std::string, std::string>::TaskSuccess(nullptr);
}

}  // namespace autumn
