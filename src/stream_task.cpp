//
// Created by J Chen on 2023/12/17.
//

#include "stream_task.h"

#include "inner_log.h"

namespace autumn {

void StreamTask::Start() {
    ilog << params_ << end_line;
    BusinessTask<std::string, std::string>::TaskSuccess(params_);
}

void StreamTask::Finish() {
    // TODO: 待实现
}

}  // namespace autumn
