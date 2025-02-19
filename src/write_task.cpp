//
// Created by J Chen on 2023/12/17.
//

#include "write_task.h"

void autumn::WriteTask::Start() {
    // TODO: 待实现
    BusinessTask<LogEntry, std::string>::TaskSuccess(params_.entry);
}

void autumn::WriteTask::Finish() {
    // TODO: 待实现
}
