//
// Created by J Chen on 2023/12/2.
//

#pragma once

#include "task_listener.h"
#include "task.h"

namespace autumn {

template <typename O, typename X>
class TaskBridge : public TaskListener<O> {
  public:
    TaskBridge() = default;
    ~TaskBridge() = default;

    void SetTask(Task<O, X>* task) { next_task_ = task; }

  public:
    Task<O, X>* next_task_ = nullptr;
};

template <typename O, typename X>
class ThenTaskBridge : public TaskBridge<O, X> {
  public:
    ThenTaskBridge() = default;
    ~ThenTaskBridge() override = default;

  public:
    void OnSuccess(O* param) {
        TaskBridge<O, X>::next_task_->SetParam(param);
        TaskBridge<O, X>::next_task_->Start();
    }

    void OnFailed() {
        TaskBridge<O, X>::next_task_->TaskFailed();
    }
};

template <typename O, typename X>
class FollowTaskBridge : public TaskBridge<O, X> {
  public:
    FollowTaskBridge() = default;
    ~FollowTaskBridge() override = default;

  public:
    void OnSuccess(O* param) {
        TaskBridge<O, X>::next_task_->SetParam(param);
        TaskBridge<O, X>::next_task_->Start();
    }

    void OnFailed() { TaskBridge<O, X>::next_task_->Start(); }
};

template <typename O, typename X>
class ThreadTaskBridge : public TaskBridge<O, X> {
    // TODO: impl thread task
};

template <typename O, typename X>
class LoopTaskBridge : public TaskBridge<O, X> {
    // TODO: impl loop task
};

template <typename O, typename X>
class RetryTaskBridge : public TaskBridge<O, X> {
    // TODO: impl retry task
};

}  // namespace autumn
