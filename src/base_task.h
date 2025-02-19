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
     * The task is bridged in Then mode.
     * @tparam X The output data type of the next task.
     * @param task Next task.
     * @return Next task.
     */
    template <typename X>
    BaseTask<O, X>* Then(BaseTask<O, X>* task) {
        auto* bridge_ = new ThenTaskBridge<O, X>();
        bridge_->SetTask(task);
        listener_ = bridge_;
        return task;
    }

    /**
     * The task is bridged in Follow mode.
     * @tparam X The output data type of the next task.
     * @param task Next task.
     * @return Next task.
     */
    template <typename X>
    BaseTask<O, X>* Follow(BaseTask<O, X>* task) {
        auto* bridge_ = new FollowTaskBridge<O, X>();
        bridge_->SetTask(task);
        listener_ = bridge_;
        return task;
    }

  public:
    void SetParam(const I& param) override {
        // TODO: 如果日志量大，这里每条日志都需要拷贝多次浪费性能。
        params_ = param;
    }

    void TaskSuccess(const O& param) override {
        if (listener_) {
            listener_->OnSuccess(param);
        }
    }

    void TaskFailed(const O& param) override {
        if (listener_) {
            listener_->OnFailed(param);
        }
    }

    void TaskFailed() override {
        if (listener_) {
            listener_->OnFailed();
        }
    }

  protected:
    TaskContext* task_context_ = nullptr;
    I params_;

  private:
    TaskListener<O>* listener_ = nullptr;
};

}  // namespace autumn
