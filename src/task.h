//
// Created by J Chen on 2025/8/30.
//

#ifndef SRC_TASK_H_
#define SRC_TASK_H_

namespace autumn {

template <typename F>
class FinalListener {
 public:
  virtual ~FinalListener() = default;
  virtual void Success(const F& f) = 0;
  virtual void Failed(const F& f) = 0;
};

template <typename I>
class Assembler {
 public:
  virtual ~Assembler() = default;
  virtual void Assemble() = 0;
  virtual void Run(const I& i) = 0;
};

template <typename I, typename O>
class Task {
 public:
  virtual ~Task() = default;
  virtual void Run(const I& i) = 0;
  virtual void Finish(const O& o) = 0;
};

template <typename O, typename F>
class TaskListener {
 public:
  virtual ~TaskListener() = default;

  virtual void NextSuccess(const O& o) = 0;
  virtual void NextFailed(const O& o) = 0;
  virtual void FinalSuccess(const F& f) = 0;
  virtual void FinalFailed(const F& f) = 0;
};

template <typename I, typename O, typename X, typename F>
class TaskBridge : public TaskListener<O, F> {
 public:
  explicit TaskBridge(std::shared_ptr<FinalListener<F>> fl) : fl_(fl) {}
  ~TaskBridge() override = default;

  void FinalSuccess(const F& f) override {
    if (fl_) {
      fl_->Success(f);
    }
  }

  void FinalFailed(const F& f) override {
    if (fl_) {
      fl_->Failed(f);
    }
  }

  void SetTask(Task<I, O>* ct, Task<O, X>* nt) {
    ct_ = ct;
    nt_ = nt;
  }

  Task<O, X>* GetNextTask() { return nt_; }
  Task<I, O>* GetCurrentTask() { return ct_; }

 private:
  Task<I, O>* ct_ = nullptr;
  Task<O, X>* nt_ = nullptr;
  std::shared_ptr<FinalListener<F>> fl_;
};

template <typename I, typename O, typename X, typename F>
class ThenTaskBridge final : public TaskBridge<I, O, X, F> {
 public:
  explicit ThenTaskBridge(std::shared_ptr<FinalListener<F>> fl)
      : TaskBridge<I, O, X, F>(fl) {}
  ~ThenTaskBridge() override = default;

  void NextSuccess(const O& o) override {
    auto* current_task = TaskBridge<I, O, X, F>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(o);

    auto* next_task = TaskBridge<I, O, X, F>::GetNextTask();
    if (!next_task) {
      return;
    }
    next_task->Run(o);
  }

  void NextFailed(const O& o) override {
    auto* current_task = TaskBridge<I, O, X, F>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(o);
  }
};

template <typename I, typename O, typename X, typename F>
class FollowTaskBridge final : public TaskBridge<I, O, X, F> {
 public:
  explicit FollowTaskBridge(std::shared_ptr<FinalListener<F>> fl)
      : TaskBridge<I, O, X, F>(fl) {}
  ~FollowTaskBridge() override = default;

  void NextSuccess(const O& o) override {
    auto* current_task = TaskBridge<I, O, X, F>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(o);

    auto* next_task = TaskBridge<I, O, X, F>::GetNextTask();
    if (!next_task) {
      return;
    }
    next_task->Run(o);
  }

  void NextFailed(const O& o) override {
    auto* current_task = TaskBridge<I, O, X, F>::GetCurrentTask();
    if (!current_task) {
      return;
    }
    current_task->Finish(o);

    auto* next_task = TaskBridge<I, O, X, F>::GetNextTask();
    if (!next_task) {
      return;
    }
    next_task->Run(o);
  }
};

#if 0
class AsyncTaskBridge;
class LoopTaskBridge;
class RetryTaskBridge;
#endif

template <typename I, typename O, typename F>
class BaseTask : public Task<I, O> {
 public:
  ~BaseTask() override = default;

  template <typename X>
  BaseTask<O, X, F>* Then(BaseTask<O, X, F>* nt) {
    auto bridge = std::make_unique<ThenTaskBridge<I, O, X, F>>(fl_);
    bridge->SetTask(this, nt);
    l_ = std::move(bridge);
    return nt;
  }

  template <typename X>
  BaseTask<O, X, F>* Follow(BaseTask<O, X, F>* nt) {
    auto bridge = std::make_unique<FollowTaskBridge<I, O, X, F>>(fl_);
    bridge->SetTask(this, nt);
    l_ = std::move(bridge);
    return nt;
  }

  void SetFinalListener(std::shared_ptr<FinalListener<F>> fl) { fl_ = fl; }

 protected:
  void NextSuccess(const O& o) {
    if (l_) {
      l_->NextSuccess(o);
    }
  }

  void NextFailed(const O& o) {
    if (l_) {
      l_->NextFailed(o);
    }
  }

  void FinalSuccess(const F& f) {
    if (l_) {
      l_->FinalSuccess(f);
    }
  }

  void FinalFailed(const F& f) {
    if (l_) {
      l_->FinalFailed(f);
    }
  }

 private:
  std::unique_ptr<TaskListener<O, F>> l_;
  std::shared_ptr<FinalListener<F>> fl_;
};

}  // namespace autumn

#endif  // SRC_TASK_H_
