//
// Created by J Chen on 2023/12/2.
//

#pragma once

namespace autumn {

template <typename O>
class TaskListener {
  public:
    TaskListener() = default;
    virtual ~TaskListener() = default;

  public:
    /**
     * Task success callback.
     * @param param The input data type of the next task.
     */
    virtual void OnSuccess(O param) = 0;

    /**
     * Task failed callback.
     * @param param The input data type of the next task.
     */
    virtual void OnFailed(O param) = 0;

    /**
     * Task failed callback.
     */
    virtual void OnFailed() = 0;
};

}  // namespace autumn