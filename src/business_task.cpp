//
// Created by J Chen on 2023/11/27.
//

#include "business_task.h"

namespace autumn {

template <typename I, typename O>
BusinessTask<I, O>::BusinessTask(TaskContext* tc) : BaseTask<I, O>(tc) {}

template <typename I, typename O>
void BusinessTask<I, O>::Start() {}

template <typename I, typename O>
void BusinessTask<I, O>::Finish() {}

}  // namespace autumn
