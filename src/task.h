//
// Created by J Chen on 2023/12/17.
//

#pragma once

template <typename I, typename O>
class Task {
  public:
    Task() = default;
    virtual ~Task() = default;

  public:  // TODO: 按照 task 生命周期来调整虚函数顺序
    /**
     * Set task param.
     */
    virtual void SetParam(I param) = 0;

    /**
     * Task start.
     */
    virtual void Start() = 0;

    /**
     * Task finish.
     */
    virtual void Finish() = 0;

    /**
     * Task success.
     * @param param Input param.
     */
    virtual void TaskSuccess(O param) = 0;

    /**
     * Task failed.
     */
    virtual void TaskFailed(O param) = 0;

    /**
     * Task failed.
     */
    virtual void TaskFailed() = 0;
};
