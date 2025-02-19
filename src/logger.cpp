//
// Created by J Chen on 2023/11/20.
//

#include "logger.h"

#include <utility>

#include "assembler_task.h"
#include "task_context.h"

namespace autumn {

Logger::Logger(const LogConfig& log_config) {
    task_context_ = new TaskContext(log_config);
    assembler_ = new AssemblerTask(task_context_);
    assembler_->Assembler();
}

Logger::~Logger() {
    delete assembler_;
    delete task_context_;
}

void Logger::Print(Message message) {
    assembler_->SetParam(std::move(message));
    assembler_->Start();
}

}  // namespace autumn
