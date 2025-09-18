//
// Created by J Chen on 2025/8/30.
//

#ifndef SRC_TASK_H_
#define SRC_TASK_H_

#include <chrono>
#include <future>
#include <thread>

namespace autumn {

template <typename I, typename O>
class Task {
 public:
  virtual ~Task() = default;
  virtual void Run(const I& in) = 0;
  virtual void Finish(const O& out) = 0;
  virtual O Result() = 0;
};

template <typename O>
class TaskListener {
 public:
  virtual ~TaskListener() = default;

  /**
   * Task success callback.
   *
   * @param out The input data type of the next task.
   */
  virtual void OnSuccess(const O& out) = 0;

  /**
   * Task failed callback.
   *
   * @param out The input data type of the next task.
   */
  virtual void OnFailed(const O& out) = 0;
};

/**
 * Task bridge.
 *
 * @tparam O The input data type of the current task.
 * @tparam O The output data type of the current task is also the input data
 * type of the next task.
 * @tparam X The output data type of the next task.
 */
template <typename I, typename O, typename X>
class TaskBridge : public TaskListener<O> {
 public:
  ~TaskBridge() override = default;
  void SetNextTask(Task<O, X>* task) { next_task_ = task; }
  Task<O, X>* GetNextTask() { return next_task_; }
  void SetCurrentTask(Task<I, O>* task) { current_task_ = task; }
  Task<I, O>* GetCurrentTask() { return current_task_; }

 private:
  Task<I, O>* current_task_ = nullptr;
  Task<O, X>* next_task_ = nullptr;
};

/**
 * Then mode task bridge.
 * If the current task succeeds, the next task is continued.
 * If the current task fails, the task is not continued.
 */
template <typename I, typename O, typename X>
class ThenTaskBridge final : public TaskBridge<I, O, X> {
 public:
  ~ThenTaskBridge() override = default;

  void OnSuccess(const O& out) override {
    auto* current_task = TaskBridge<I, O, X>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(out);

    auto* next_task = TaskBridge<I, O, X>::GetNextTask();
    if (!next_task) {
      return;
    }
    next_task->Run(out);
  }

  void OnFailed(const O& out) override {
    auto* current_task = TaskBridge<I, O, X>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(out);
  }
};

/**
 * Follow mode task bridge.
 * Continue to execute the next task regardless of whether the current task is
 * successfully executed.
 */
template <typename I, typename O, typename X>
class FollowTaskBridge final : public TaskBridge<I, O, X> {
 public:
  ~FollowTaskBridge() override = default;

  void OnSuccess(const O& out) override {
    auto* current_task = TaskBridge<I, O, X>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(out);

    auto* next_task = TaskBridge<I, O, X>::GetNextTask();
    if (!next_task) {
      return;
    }
    next_task->Run(out);
  }

  void OnFailed(const O& out) override {
    auto* current_task = TaskBridge<I, O, X>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(out);

    auto* next_task = TaskBridge<I, O, X>::GetNextTask();
    if (!next_task) {
      return;
    }
    next_task->Run(out);
  }
};

#if 0
template <typename I, typename O, typename X>
class AsyncTaskBridge : public TaskBridge<I, O, X> {
    // TODO(null186): 待实现
};

template <typename I, typename O, typename X>
class LoopTaskBridge : public TaskBridge<I, O, X> {
    // TODO(null186): 待实现
};

template <typename I, typename O, typename X>
class RetryTaskBridge : public TaskBridge<I, O, X> {
  public:
    // TODO(null186): 待实现

  private:
    int max_retries_ = 0;
    int retry_count_ = 0;
    std::chrono::milliseconds delay_ = std::chrono::milliseconds(0);
};
#endif

template <typename I, typename O>
class BaseTask : public Task<I, O> {
 public:
  ~BaseTask() override = default;

  /**
   * The task is bridged in Then mode.
   *
   * @tparam X The output data type of the next task.
   * @param next_task Next task.
   * @return Next task.
   */
  template <typename X>
  BaseTask<O, X>* Then(BaseTask<O, X>* next_task) {
    auto bridge = std::make_unique<ThenTaskBridge<I, O, X>>();
    bridge->SetCurrentTask(this);
    bridge->SetNextTask(next_task);
    listener_ = std::move(bridge);
    return next_task;
  }

  /**
   * The task is bridged in Follow mode.
   *
   * @tparam X The output data type of the next task.
   * @param next_task Next task.
   * @return Next task.
   */
  template <typename X>
  BaseTask<O, X>* Follow(BaseTask<O, X>* next_task) {
    auto bridge = std::make_unique<FollowTaskBridge<I, O, X>>();
    bridge->SetCurrentTask(this);
    bridge->SetNextTask(next_task);
    listener_ = std::move(bridge);
    return next_task;
  }

  O Result() final { return out_; }

 protected:
  void Success(const O& out) {
    if (listener_) {
      listener_->OnSuccess(out);
    }
    out_ = out;
  }

  void Failed(const O& out) {
    if (listener_) {
      listener_->OnFailed(out);
    }
    out_ = out;
  }

 private:
  O out_;
  std::unique_ptr<TaskListener<O>> listener_;
};

}  // namespace autumn

#endif  // SRC_TASK_H_
