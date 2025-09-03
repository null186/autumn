//
// Created by J Chen on 2023/11/22.
//

#include "compress.h"

#include "utils/inner_log.h"

namespace autumn {

void autumn::CompressTask::Run() {
  ilog << "Compress task start" << end_line;
  // TODO(null186): 待实现
  Success(params_);
}

void CompressTask::Finish(const LogEntry& param) {
  ilog << "Compress task finish" << end_line;
  // TODO(null186): 待实现
}

}  // namespace autumn
