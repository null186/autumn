//
// Created by J Chen on 2023/12/17.
//

#include "write.h"

#include "src/utils/inner_log.h"

namespace autumn {

WriteTask::WriteTask(const LogConfig& config)
    : BaseTask(),
      file_writer_(std::make_unique<FileWriter>(
          config.max_files, config.max_file_size, config.work_dir)) {}

void WriteTask::Run() {
  if (file_writer_) {
    file_writer_->Write(params_.entry);
    Success(params_.entry);
  } else {
    ilog << "pointer WriteTask::file_writer_ is nullptr." << end_line;
    Failed(params_.entry);
  }
}

void WriteTask::Finish(const std::string& param) {
  // TODO(null186): 待实现
}

}  // namespace autumn
