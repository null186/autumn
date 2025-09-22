//
// Created by J Chen on 2023/12/17.
//

#include "src/task/stream.h"

#define PRINT_TO_STDOUT(s) \
  do {                     \
    printf("%s\n", s);     \
    (void)fflush(stdout);  \
  } while (0)

namespace autumn {

void StreamTask::Run(const std::string& in) {
  PRINT_TO_STDOUT(in.c_str());
  NextSuccess(in);
}

void StreamTask::Finish(const std::string& out) {
  // TODO(null186): 待实现
}

}  // namespace autumn
