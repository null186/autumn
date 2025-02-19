//
// Created by J Chen on 2023/12/2.
//

#pragma once

#include <vector>

namespace autumn {

class TaskContext;

template <typename I, typename O>
class BaseTask;

class TaskAssembler {
  public:
    explicit TaskAssembler(TaskContext* tc);
    virtual ~TaskAssembler();

  public:
    void Assembler();
    void Start();

  private:
    TaskContext* task_context_ = nullptr;

  private:
    BaseTask<std::string, std::string>* task_list_ = nullptr;
};

}  // namespace autumn
