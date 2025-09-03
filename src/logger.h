//
// Created by J Chen on 2023/11/20.
//

#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H

#include <cstdint>
#include <cstdio>
#include <string>

#include "assembler.h"
#include "autumn/log.h"
#include "log_def.h"

namespace autumn {

class Logger {
 public:
  explicit Logger(const LogConfig& config);
  ~Logger() = default;

 public:
  /**
   * Print log.
   *
   * @param message
   */
  void Print(const LogMessage& message);

 private:
  std::unique_ptr<Assembler> assembler_;
};

}  // namespace autumn

#endif  // SRC_LOGGER_H
