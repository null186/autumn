//
// Created by J Chen on 2023/11/22.
//

#include "src/task/compress.h"

#include "src/utils/inner_log.h"

namespace autumn {

void CompressTask::Run(const LogEntry& in) {
  ilog << "Compress task start" << end_line;
  // TODO(null186): 待实现
  NextSuccess(in);
}

void CompressTask::Finish(const LogEntry& out) {
  ilog << "Compress task finish" << end_line;
  // TODO(null186): 待实现
}

}  // namespace autumn
