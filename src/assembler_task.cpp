//
// Created by J Chen on 2023/12/2.
//

#include "assembler_task.h"

#include "compress_task.h"
#include "encrypt_task.h"
#include "format_task.h"
#include "logger.h"
#include "stream_task.h"
#include "write_task.h"

namespace autumn {

AssemblerTask::AssemblerTask(TaskContext* tc)
    : BaseTask<LogMessage, LogMessage>(tc), task_context_(tc) {
    format_task_ = new FormatTask(task_context_);
    compress_task_ = new CompressTask(task_context_);
    encrypt_task_ = new EncryptTask(task_context_);
    stream_task_ = new StreamTask(task_context_);
    write_task_ = new WriteTask(task_context_);
}

AssemblerTask::~AssemblerTask() {
    delete format_task_;
    delete compress_task_;
    delete encrypt_task_;
    delete stream_task_;
    delete write_task_;
}

void AssemblerTask::Assembler() {
    BaseTask<LogMessage, LogMessage>::Then(format_task_)
            ->Then(compress_task_)
            ->Then(encrypt_task_)
            ->Then(write_task_)
            ->Follow(stream_task_);
}

void AssemblerTask::SetParam(const LogMessage& param) {
    BaseTask<LogMessage, LogMessage>::SetParam(param);
}

void AssemblerTask::Start() {
    // TODO: 详细校验 LogMessage 有效性。
    if (params_.message.empty()) {
        BaseTask<LogMessage, LogMessage>::TaskFailed(BaseTask<LogMessage, LogMessage>::params_);
    } else {
        BaseTask<LogMessage, LogMessage>::TaskSuccess(BaseTask<LogMessage, LogMessage>::params_);
    }
}

void AssemblerTask::Finish() {
    // TODO: 待实现
}

}  // namespace autumn
