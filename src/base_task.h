//
// Created by J Chen on 2023/11/22.
//

#pragma once

#define EXPORT __attribute__((visibility("default")))

namespace autumn {

class TaskContext;

template <typename I, typename O>
class TaskBridge;

template <typename I, typename O>
class BaseTask {
  public:
    explicit BaseTask(TaskContext* tc);
    virtual ~BaseTask();

  public:
    /**
     * 设置任务参数
     */
    void SetParam(I* param);

    /**
     * 追加任务
     * @tparam Y
     * @param task
     * @return
     */
    template <typename Y>
    BaseTask<O, Y>* Then(BaseTask<O, Y>* task);

    /**
     * 追加任务
     * @tparam Y
     * @param task
     * @return
     */
    template <typename Y>
    BaseTask<O, Y>* Follow(BaseTask<O, Y>* task);

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
    void TaskSuccess(O* param);

    /**
     * 任务失败
     */
    void TaskFailed();

  private:
    TaskContext* task_context_ = nullptr;
    I* params_ = nullptr;

  private:
    TaskBridge<I, O>* bridge_ = nullptr;
};

}  // namespace autumn
