//
// Created by J Chen on 2023/12/2.
//

#include "assembler.h"

namespace autumn {

Assembler::Assembler(const LogConfig& config)
    : format_task_(std::make_unique<FormatTask>(config)),
      compress_task_(std::make_unique<CompressTask>(config)),
      encrypt_task_(std::make_unique<EncryptTask>(config)),
      stream_task_(std::make_unique<StreamTask>(config)),
      write_task_(std::make_unique<WriteTask>(config)) {}

void Assembler::Assemble() {
  format_task_.get()
      ->Then(compress_task_.get())
      ->Then(encrypt_task_.get())
      ->Then(write_task_.get())
      ->Follow(stream_task_.get());
}

void Assembler::Run(const LogMessage& message) {
  format_task_->SetParam(message);
  format_task_->Run();
}

}  // namespace autumn
