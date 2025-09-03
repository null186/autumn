//
// Created by J Chen on 2023/11/20.
//

#include "src/logger.h"

namespace autumn {

Logger::Logger(const LogConfig& config) {
  assembler_ = std::make_unique<Assembler>(config);
  assembler_->Assemble();
}

void Logger::Print(const LogMessage& message) {
  assembler_->Run(message);
}

}  // namespace autumn
