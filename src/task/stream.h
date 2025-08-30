//
// Created by J Chen on 2023/12/17.
//

#ifndef SRC_TASK_STREAM_H_
#define SRC_TASK_STREAM_H_

#include "autumn/config.h"
#include "task.h"

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

#endif  // SRC_TASK_STREAM_H_
