//
// Created by J Chen on 2023/11/22.
//

#include "compress_task.h"

#include "inner_log.h"

namespace autumn {

void autumn::CompressTask::Start() {
    ilog << "Compress task start" << end_line;
    // TODO: 待实现
    TaskSuccess(params_);
}

void CompressTask::Finish() {
    ilog << "Compress task finish" << end_line;
    // TODO: 待实现
}

}  // namespace autumn
