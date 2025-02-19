//
// Created by J Chen on 2023/12/2.
//

#include "task_assembler.h"

#include "compress_task.h"
#include "encrypt_task.h"
#include "format_task.h"
#include "logger.h"
#include "stream_task.h"
#include "write_task.h"

namespace autumn {

TaskAssembler::TaskAssembler(TaskContext* tc) : BaseTask<Message, Message>(tc), task_context_(tc) {}

TaskAssembler::~TaskAssembler() {
    if (format_task_) {
        delete format_task_;
    }

    if (compress_task_) {
        delete compress_task_;
    }

    if (encrypt_task_) {
        delete encrypt_task_;
    }

    if (stream_task_) {
        delete stream_task_;
    }

    if (write_task_) {
        delete write_task_;
    }
}

void TaskAssembler::Assembler() {
    format_task_ = new FormatTask(task_context_);
    compress_task_ = new CompressTask(task_context_);
    encrypt_task_ = new EncryptTask(task_context_);
    stream_task_ = new StreamTask(task_context_);
    write_task_ = new WriteTask(task_context_);

    BaseTask<Message, Message>::Then(format_task_)
            ->Then(compress_task_)
            ->Then(encrypt_task_)
            ->Then(stream_task_)
            ->Follow(write_task_);
}

void TaskAssembler::SetParam(Message param) {
    BaseTask<Message, Message>::SetParam(param);
}

void TaskAssembler::Start() {
    if (params_.content.empty()) {
        BaseTask<Message, Message>::TaskFailed(BaseTask<Message, Message>::params_);
    } else {
        BaseTask<Message, Message>::TaskSuccess(BaseTask<Message, Message>::params_);
    }
}

void TaskAssembler::Finish() {
    // TODO: 待实现
}

}  // namespace autumn
