//
// Created by J Chen on 2023/12/2.
//

#include "task_bridge.h"

#include "base_task.h"

namespace autumn {

template <typename I, typename O>
void TaskBridge<I, O>::SetTask(BaseTask<I, O>* task) {
    next_task_ = task;
}

template <typename I, typename O>
void ThenTaskBridge<I, O>::OnSuccess(O* param) {
    TaskBridge<I, O>::next_task_->SetParam(param);
    TaskBridge<I, O>::next_task_->Start();
}

template <typename I, typename O>
void ThenTaskBridge<I, O>::OnFailed() {
    // TODO: task failed
}

template <typename I, typename O>
void FollowTaskBridge<I, O>::OnSuccess(O* param) {
    TaskBridge<I, O>::next_task_->SetParam(param);
    TaskBridge<I, O>::next_task_->Start();
}

template <typename I, typename O>
void FollowTaskBridge<I, O>::OnFailed() {
    // TODO: task failed
}

}  // namespace autumn