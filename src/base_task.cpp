//
// Created by J Chen on 2023/11/22.
//

#include "base_task.h"

#include "task_bridge.h"

namespace autumn {

template <typename I, typename O>
BaseTask<I, O>::BaseTask(TaskContext* tc) : task_context_(tc) {}

template <typename I, typename O>
BaseTask<I, O>::~BaseTask() {
    if (bridge_ != nullptr) {
        delete bridge_;
        bridge_ = nullptr;
    }
}

template <typename I, typename O>
void BaseTask<I, O>::SetParam(I* param) {
    params_ = param;
}

template <typename I, typename O>
template <typename Y>
BaseTask<O, Y>* BaseTask<I, O>::Then(BaseTask<O, Y>* task) {
    bridge_ = new ThenTaskBridge<O, Y>();
    bridge_->SetTask(task);
    return task;
}

template <typename I, typename O>
template <typename Y>
BaseTask<O, Y>* BaseTask<I, O>::Follow(BaseTask<O, Y>* task) {
    bridge_ = new FollowTaskBridge<O, Y>();
    bridge_->SetTask(task);
    return task;
}

template <typename I, typename O>
void BaseTask<I, O>::TaskSuccess(O* param) {
    bridge_->OnSuccess(param);
}

template <typename I, typename O>
void BaseTask<I, O>::TaskFailed() {
    bridge_->OnFailed();
}

}  // namespace autumn