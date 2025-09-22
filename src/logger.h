//
// Created by J Chen on 2023/11/20.
//

#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include "autumn/log.h"
#include "src/assembler.h"
#include "src/log_def.h"

namespace autumn {

class Logger {
 public:
  explicit Logger(const LogConfig& config);
  ~Logger() = default;

  /**
   * Print log.
   *
   * @param message
   */
  void Print(const LogMessage& message);

 private:
  std::unique_ptr<UserAssembler> user_assembler_;
};

}  // namespace autumn

#endif  // SRC_LOGGER_H_
