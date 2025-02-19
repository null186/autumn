//
// Created by J Chen on 2023/11/22.
//

#include "encrypt_task.h"

#include "inner_log.h"

namespace autumn {

void EncryptTask::Start() {
    ilog << "Encrypt task start" << end_line;
    TaskSuccess(nullptr);
}

void EncryptTask::Finish() {
    ilog << "Encrypt task finish" << end_line;
}

}  // namespace autumn
