//
// Created by J Chen on 2023/11/20.
//

#include "logger.h"

#include <utility>

#include "task_assembler.h"
#include "task_context.h"

namespace autumn {

autumn::Logger::Logger() {
    task_context_ = new TaskContext();
    assembler_ = new TaskAssembler(task_context_);
    assembler_->Assembler();
}

autumn::Logger::~Logger() {
    delete assembler_;
    delete task_context_;
}

void autumn::Logger::Print(Message message) {
    assembler_->SetParam(std::move(message));
    assembler_->Start();
}

}  // namespace autumn
