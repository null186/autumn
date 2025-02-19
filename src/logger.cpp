//
// Created by J Chen on 2023/11/20.
//

#include "logger.h"

#include <cinttypes>

#include "task_assembler.h"
#include "task_context.h"

namespace autumn {

autumn::Logger::Logger() {
    task_context_ = new TaskContext();
    assembler_ = new TaskAssembler(task_context_);

    assembler_->Assembler();
}

autumn::Logger::~Logger() {
    delete task_context_;
    delete assembler_;
}

void autumn::Logger::Print(Message message) {
    char buff[4096] = {0};
    std::snprintf(buff, 4096, "[%s][%d][%" PRIu64 "][%s][%s][%d] %s", message.time,
                  message.log_type, message.thread_id, message.tag, message.file, message.line,
                  message.content.c_str());
    printf("%s\n", buff);

    assembler_->Start();
}

}  // namespace autumn
