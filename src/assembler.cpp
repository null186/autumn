//
// Created by J Chen on 2023/12/2.
//

#include "src/assembler.h"

namespace autumn {

void UserFinalListener::Success(const std::string& f) {

}

void UserFinalListener::Failed(const std::string& f) {

}

UserAssembler::UserAssembler(const LogConfig& config)
    : format_task_(std::make_unique<FormatTask>(config)),
      compress_task_(std::make_unique<CompressTask>(config)),
      encrypt_task_(std::make_unique<EncryptTask>(config)),
      stream_task_(std::make_unique<StreamTask>(config)),
      write_task_(std::make_unique<WriteTask>(config)) {}

void UserAssembler::Assemble() {
  const auto final_task = format_task_->Then(compress_task_.get())
                              ->Then(encrypt_task_.get())
                              ->Then(write_task_.get())
                              ->Follow(stream_task_.get());

  final_task->SetFinalListener(std::make_shared<UserFinalListener>());
}

void UserAssembler::Run(const LogMessage& in) { format_task_->Run(in); }

}  // namespace autumn
