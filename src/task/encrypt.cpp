//
// Created by J Chen on 2023/11/22.
//

#include "src/task/encrypt.h"

#include "src/utils/inner_log.h"

namespace autumn {

void EncryptTask::Run(const LogEntry& in) {
  ilog << "Encrypt task start" << end_line;
  // TODO(null186): 待实现
  NextSuccess(in);
}

void EncryptTask::Finish(const LogEntry& out) {
  ilog << "Encrypt task finish" << end_line;
  // TODO(null186): 待实现
}

}  // namespace autumn
