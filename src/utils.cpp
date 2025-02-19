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

uint64_t autumn::Utils::GetThreadId() {
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

int64_t autumn::Utils::GetLocalTime() {
    return std::chrono::duration_cast<std::chrono::seconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
}

inline struct tm* local_time(const time_t* time, struct tm* result) {
#ifdef _WIN32
    localtime_s(result, time);
#else
    localtime_r(time, result);
#endif
}

std::string autumn::Utils::NsToString(int64_t time) {
    char buff[32] = {0};
    const std::time_t t = time;
    struct std::tm tm {};
    local_time(&t, &tm);
    std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &tm);
    return buff;
}
