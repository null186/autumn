//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "task.h"
#include "autumn/config.h"

namespace autumn {

class StreamTask : public BaseTask<std::string, std::string> {
 public:
  explicit StreamTask(const LogConfig& config)
      : BaseTask<std::string, std::string>() {}
  ~StreamTask() override = default;

 public:
  void Run() override;
  void Finish(const std::string& param) override;
};
}  // namespace autumn
