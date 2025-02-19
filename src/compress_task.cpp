//
// Created by J Chen on 2023/11/22.
//

#include "compress_task.h"

namespace autumn {

void autumn::CompressTask::Start() {
    BaseTask<int, bool>::TaskSuccess(nullptr);
}

void CompressTask::Finish() {}

}  // namespace autumn
