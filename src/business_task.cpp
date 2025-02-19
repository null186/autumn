//
// Created by J Chen on 2023/11/27.
//

#include "business_task.h"

namespace autumn {

template <typename I, typename O>
void BusinessTask<I, O>::Start() {
    std::cout << "Start" << std::endl;
}

template <typename I, typename O>
void BusinessTask<I, O>::Finish() {
    std::cout << "Finish" << std::endl;
}

}  // namespace autumn
