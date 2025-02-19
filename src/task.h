//
// Created by J Chen on 2023/12/17.
//

#pragma once

template <typename I, typename O>
class Task {
  public:
    Task() = default;
    virtual ~Task() = default;

  public:
    /**
     * 设置任务参数
     */
    virtual void SetParam(I* param) = 0;

    /**
     * 任务开始
     */
    virtual void Start() = 0;

    /**
     * 任务结束
     */
    virtual void Finish() = 0;

    /**
     * 任务成功
     */
    virtual void TaskSuccess(O* param) = 0;

    /**
     * 任务失败
     */
    virtual void TaskFailed() = 0;
};
