//
// Created by J Chen on 2023/12/17.
//

#include "stream.h"

#define PRINT_TO_STDOUT(s) \
  do {                     \
    printf("%s\n", s);     \
    (void)fflush(stdout);  \
  } while (0)

namespace autumn {

void StreamTask::Run() {
  PRINT_TO_STDOUT(params_.c_str());
  BaseTask<std::string, std::string>::Success(params_);
}

void StreamTask::Finish(const std::string& param) {
  // TODO: 待实现
}

}  // namespace autumn
