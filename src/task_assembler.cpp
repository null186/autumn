//
// Created by J Chen on 2023/12/2.
//

#include "task_assembler.h"

#include "compress_task.h"
#include "encrypt_task.h"

namespace autumn {

TaskAssembler::TaskAssembler(TaskContext* tc) : BaseTask<void, void>(tc), task_context_(tc) {}

TaskAssembler::~TaskAssembler() {
    if (encrypt_task_) {
        delete encrypt_task_;
    }

    if (compress_task_) {
        delete compress_task_;
    }
}

void TaskAssembler::Assembler() {
    encrypt_task_ = new EncryptTask(task_context_);
    compress_task_ = new CompressTask(task_context_);

    BaseTask<void, void>::Then(encrypt_task_)->Then(compress_task_);
}

void TaskAssembler::SetParam(void* param) {
    BaseTask::SetParam(param);
}

void TaskAssembler::Start() {
    if (params_) {
        BaseTask<void, void>::TaskSuccess(BaseTask<void, void>::params_);
    } else {
        BaseTask<void, void>::TaskFailed();
    }
}

void TaskAssembler::Finish() {
    //
}

}  // namespace autumn
