//
// Created by J Chen on 2023/11/22.
//

#include "compress_task.h"

namespace autumn {

CompressTask::CompressTask(TaskContext* tc) : BusinessTask<std::string, std::string>(tc) {}

autumn::CompressTask::~CompressTask() = default;

void autumn::CompressTask::Start() {
    BaseTask<std::string, std::string>::TaskSuccess(nullptr);
}

}  // namespace autumn
