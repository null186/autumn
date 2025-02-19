//
// Created by J Chen on 2023/12/17.
//

#include "stream_task.h"

#define PRINT_TO_STDOUT(s)    \
    do {                      \
        printf("%s\n", s);    \
        (void)fflush(stdout); \
    } while (0)

namespace autumn {

void StreamTask::Start() {
    PRINT_TO_STDOUT(params_.c_str());
    BusinessTask<std::string, std::string>::TaskSuccess(params_);
}

void StreamTask::Finish() {
    // TODO: 待实现
}

}  // namespace autumn
