//
// Created by J Chen on 2023/11/22.
//

#include "encrypt_task.h"

namespace autumn {

void EncryptTask::Start() {
    BaseTask<void, int>::TaskSuccess(nullptr);
}

void EncryptTask::Finish() {}

}  // namespace autumn
