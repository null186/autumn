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
     * Set task param.
     *
     * @param param Task param.
     */
    virtual void SetParam(const I& param) = 0;

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
     *
     * @param param Input param.
     */
    virtual void TaskSuccess(const O& param) = 0;

    /**
     * Task failed.
     */
    virtual void TaskFailed(const O& param) = 0;

    /**
     * Task failed.
     */
    virtual void TaskFailed() = 0;
};
