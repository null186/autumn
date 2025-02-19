//
// Created by J Chen on 2023/12/2.
//

#pragma once

#include "task.h"
#include "task_listener.h"
#include "utils.h"

namespace autumn {

/**
 * Task bridge.
 * @tparam O The output data type of the current task is also the input data type of the next task.
 * @tparam X The output data type of the next task.
 */
template <typename O, typename X>
class TaskBridge : public TaskListener<O> {
  public:
    TaskBridge() = default;
    ~TaskBridge() = default;

    void SetTask(Task<O, X>* task) { next_task_ = task; }

  public:
    Task<O, X>* next_task_ = nullptr;
};

/**
 * Then mode task bridge.
 * If the current task succeeds, the next task is continued.
 * If the current task fails, the task is not continued.
 */
template <typename O, typename X>
class ThenTaskBridge : public TaskBridge<O, X> {
  public:
    ThenTaskBridge() = default;
    ~ThenTaskBridge() override = default;

  public:
    void OnSuccess(O param) override {
        auto* next_task = TaskBridge<O, X>::next_task_;
        if (!next_task) {
            return;
        }
        next_task->SetParam(param);
        next_task->Start();
    }

    void OnFailed(O UNUSED param) override {
        // TODO: 临时方案
    }

    void OnFailed() override {
        auto* next_task = TaskBridge<O, X>::next_task_;
        if (!next_task) {
            return;
        }
        next_task->TaskFailed();
    }
};

/**
 * Follow mode task bridge.
 * Continue to execute the next task regardless of whether the current task is successfully
 * executed.
 */
template <typename O, typename X>
class FollowTaskBridge : public TaskBridge<O, X> {
  public:
    FollowTaskBridge() = default;
    ~FollowTaskBridge() override = default;

  public:
    void OnSuccess(O param) override {
        auto* next_task = TaskBridge<O, X>::next_task_;
        if (!next_task) {
            return;
        }
        next_task->SetParam(param);
        next_task->Start();
    }

    void OnFailed(O param) override {
        auto* next_task = TaskBridge<O, X>::next_task_;
        if (!next_task) {
            return;
        }
        next_task->SetParam(param);
        next_task->Start();
    }

    void OnFailed() override {
        // TODO: 临时方案
    }
};

template <typename O, typename X>
class ThreadTaskBridge : public TaskBridge<O, X> {
    // TODO: 待实现
};

template <typename O, typename X>
class LoopTaskBridge : public TaskBridge<O, X> {
    // TODO: 待实现
};

template <typename O, typename X>
class RetryTaskBridge : public TaskBridge<O, X> {
    // TODO: 待实现
};

}  // namespace autumn
