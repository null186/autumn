//
// Created by J Chen on 2023/11/22.
//

#include "compress_task.h"

#include "inner_log.h"

namespace autumn {

void autumn::CompressTask::Start() {
    ilog << "Compress task start" << end_line;
    TaskSuccess(nullptr);
}

void CompressTask::Finish() {
    ilog << "Compress task finish" << end_line;
}

}  // namespace autumn
