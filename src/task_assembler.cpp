//
// Created by J Chen on 2023/12/2.
//

#include "task_assembler.h"

#include "compress_task.h"
#include "encrypt_task.h"

namespace autumn {

TaskAssembler::TaskAssembler(TaskContext* tc) : task_context_(tc) {}

TaskAssembler::~TaskAssembler() {
    delete task_list_;
}

void TaskAssembler::Assembler() {
    auto* encrypt_task = new EncryptTask(task_context_);
    auto* compress_task = new CompressTask(task_context_);

    encrypt_task->Then(compress_task);

    task_list_ = encrypt_task;
}

void TaskAssembler::Start() {
    task_list_->Start();
}

}  // namespace autumn
