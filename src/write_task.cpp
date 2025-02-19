//
// Created by J Chen on 2023/12/17.
//

#include "write_task.h"

#include "file_writer.h"
#include "inner_log.h"
#include "task_context.h"

namespace autumn {

WriteTask::WriteTask(autumn::TaskContext* tc) : BusinessTask<LogEntry, std::string>(tc) {
    file_writer_ = new FileWriter(tc->GetMaxFiles(), tc->GetMaxFileSize(), tc->GetWorkDir());
}

WriteTask::~WriteTask() {
    if (file_writer_) {
        delete file_writer_;
        file_writer_ = nullptr;
    }
}

void WriteTask::Start() {
    if (file_writer_) {
        file_writer_->Write(params_.entry);
        BusinessTask<LogEntry, std::string>::TaskSuccess(params_.entry);
    } else {
        ilog << "pointer WriteTask::file_writer_ is nullptr." << end_line;
        BusinessTask<LogEntry, std::string>::TaskFailed(params_.entry);
    }
}

void WriteTask::Finish() {
    // TODO: 待实现
}

}  // namespace autumn
