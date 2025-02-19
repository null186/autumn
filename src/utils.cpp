//
// Created by J Chen on 2023/11/14.
//

#include "utils.h"

#if defined(__ANDROID__)
//
#elif defined(_WIN32)
//
#elif defined(__APPLE__)
#include <sys/syscall.h>
#include <unistd.h>
#elif defined(__linux)
//
#endif

uint64_t autumn::Utils::get_thread_id() {
#if defined(__ANDROID__)
    //
#elif defined(_WIN32)
    //
#elif defined(__APPLE__)
    return syscall(SYS_thread_selfid);
#elif defined(__linux)
    //
#endif
}

uint64_t autumn::Utils::get_time_ns() {
    return 0;
}

std::string autumn::Utils::ns_to_string(uint64_t ns) {
    return {};
}
