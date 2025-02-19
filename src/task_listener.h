//
// Created by J Chen on 2023/12/2.
//

#pragma once

namespace autumn {

template <typename I, typename O>
class TaskListener {
  public:
    virtual ~TaskListener() = default;

  public:
    virtual void OnSuccess(O* param) = 0;
    virtual void OnFailed() = 0;
};

}  // namespace autumn