//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include "task.h"
#include "task_bridge.h"

namespace autumn {

class TaskContext;

template <typename I, typename O>
class BaseTask : public Task<I, O> {
  public:
    explicit BaseTask(TaskContext* tc) : task_context_(tc) {}
    virtual ~BaseTask() = default;

  public:
    /**
     * 追加任务
     * @tparam X
     * @param task
     * @return
     */
    template <typename X>
    BaseTask<O, X>* Then(BaseTask<O, X>* task) {
        auto* bridge_ = new ThenTaskBridge<O, X>();
        bridge_->SetTask(task);
        listener_ = bridge_;
        return task;
    }

    /**
     * 追加任务
     * @tparam X
     * @param task
     * @return
     */
    template <typename X>
    BaseTask<O, X>* Follow(BaseTask<O, X>* task) {
        auto* bridge_ = new FollowTaskBridge<O, X>();
        bridge_->SetTask(task);
        listener_ = bridge_;
        return task;
    }

  public:
    void SetParam(I* param) override { params_ = param; }

    void TaskSuccess(O* param) override {
        if (listener_) {
            listener_->OnSuccess(param);
        }
    }

    void TaskFailed() override {
        if (listener_) {
            listener_->OnFailed();
        }
    }

  private:
    TaskContext* task_context_ = nullptr;
    I* params_ = nullptr;

  private:
    TaskListener<O>* listener_ = nullptr;
};

}  // namespace autumn
