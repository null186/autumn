//
// Created by J Chen on 2023/12/2.
//

#ifndef SRC_ASSEMBLER_H_
#define SRC_ASSEMBLER_H_

#include "autumn/log.h"
#include "src/log_def.h"
#include "src/task.h"
#include "src/task/compress.h"
#include "src/task/encrypt.h"
#include "src/task/format.h"
#include "src/task/stream.h"
#include "src/task/write.h"

namespace autumn {

class UserFinalListener final : public FinalListener<std::string> {
 public:
  ~UserFinalListener() override = default;
  void Success(const std::string& f) override;
  void Failed(const std::string& f) override;
};

class UserAssembler final : public Assembler<LogMessage> {
 public:
  explicit UserAssembler(const LogConfig& config);
  ~UserAssembler() override = default;
  void Assemble() override;
  void Run(const LogMessage& in) override;

 private:
  std::unique_ptr<FormatTask> format_task_;
  std::unique_ptr<CompressTask> compress_task_;
  std::unique_ptr<EncryptTask> encrypt_task_;
  std::unique_ptr<StreamTask> stream_task_;
  std::unique_ptr<WriteTask> write_task_;
};

}  // namespace autumn

#endif  // SRC_ASSEMBLER_H_
