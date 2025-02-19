//
// Created by J Chen on 2023/11/22.
//

#pragma once

#include "task_bridge.h"

namespace autumn {

class TaskContext;

template <typename O, typename X>
class TaskBridge;

template <typename O, typename X>
class ThenTaskBridge;

template <typename O, typename X>
class FollowTaskBridge;

template <typename I, typename O>
class BaseTask {
  public:
    explicit BaseTask(TaskContext* tc) : task_context_(tc) {}
    virtual ~BaseTask() = default;

  public:
    /**
     * 设置任务参数
     */
    void SetParam(I* param) { params_ = param; }

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
    /**
     * 任务开始
     */
    virtual void Start() = 0;

    /**
     * 任务结束
     */
    virtual void Finish() = 0;

  public:
    /**
     * 任务成功
     */
    void TaskSuccess(O* param) {
        if (listener_) {
            listener_->OnSuccess(param);
        }
    }

    /**
     * 任务失败
     */
    void TaskFailed() {
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
