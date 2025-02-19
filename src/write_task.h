//
// Created by J Chen on 2023/12/17.
//

#pragma once

#include "business_task.h"

namespace autumn {

class FileWriter;

class WriteTask : public BusinessTask<LogEntry, std::string> {
  public:
    explicit WriteTask(TaskContext* tc);
    ~WriteTask() override;

  public:
    void Start() override;
    void Finish() override;

  private:
    FileWriter* file_writer_ = nullptr;
};

}  // namespace autumn