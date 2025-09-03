//
// Created by J Chen on 2023/12/17.
//

#include "write.h"

#include "utils/inner_log.h"
#include "writer/file.h"

namespace autumn {

WriteTask::WriteTask(const LogConfig& config)
    : BaseTask<LogEntry, std::string>() {
  file_writer_ =
      new FileWriter(config.max_files, config.max_file_size, config.work_dir);
}

WriteTask::~WriteTask() {
  if (file_writer_) {
    delete file_writer_;
    file_writer_ = nullptr;
  }
}

void WriteTask::Run() {
  if (file_writer_) {
    file_writer_->Write(params_.entry);
    BaseTask<LogEntry, std::string>::Success(params_.entry);
  } else {
    ilog << "pointer WriteTask::file_writer_ is nullptr." << end_line;
    BaseTask<LogEntry, std::string>::Failed(params_.entry);
  }
}

void WriteTask::Finish(const std::string& param) {
  // TODO(null186): 待实现
}

}  // namespace autumn
