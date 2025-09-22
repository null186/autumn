//
// Created by J Chen on 2023/11/20.
//

#include "src/logger.h"

namespace autumn {

Logger::Logger(const LogConfig& config) {
  user_assembler_ = std::make_unique<UserAssembler>(config);
  user_assembler_->Assemble();
}

void Logger::Print(const LogMessage& message) {
  user_assembler_->Run(message);
}

}  // namespace autumn
