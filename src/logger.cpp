//
// Created by J Chen on 2023/11/20.
//

#include "logger.h"

#include "assembler.h"

namespace autumn {

Logger::Logger(const LogConfig& log_config) {
  assembler_ = new AssemblerTask(log_config);
  assembler_->Assembler();
}

Logger::~Logger() {
  delete assembler_;
}

void Logger::Print(const LogMessage& message) {
  assembler_->SetParam(message);
  assembler_->Run();
}

}  // namespace autumn
