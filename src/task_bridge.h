//
// Created by J Chen on 2023/12/2.
//

#pragma once

#include "task_listener.h"

namespace autumn {

template <typename I, typename O>
class BaseTask;

template <typename I, typename O>
class TaskBridge : public TaskListener<I, O> {
  public:
    ~TaskBridge() = default;
    void SetTask(BaseTask<I, O>* task);

  protected:
    BaseTask<I, O>* next_task_ = nullptr;
};

template <typename I, typename O>
class ThenTaskBridge : public TaskBridge<I, O> {
  public:
    ~ThenTaskBridge() override = default;

  public:
    void OnSuccess(O* param) override;
    void OnFailed() override;
};

template <typename I, typename O>
class FollowTaskBridge : public TaskBridge<I, O> {
  public:
    ~FollowTaskBridge() override = default;

  public:
    void OnSuccess(O* param) override;
    void OnFailed() override;
};

template <typename I, typename O>
class ThreadTaskBridge : public TaskBridge<I, O> {
    // TODO: impl thread task
};

template <typename I, typename O>
class LoopTaskBridge : public TaskBridge<I, O> {
    // TODO: impl loop task
};

template <typename I, typename O>
class RetryTaskBridge : public TaskBridge<I, O> {
    // TODO: impl retry task
};

}  // namespace autumn
