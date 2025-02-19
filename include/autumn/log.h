//
// Created by J Chen on 2022/9/25.
//

#pragma once

#include <cstdint>

namespace autumn {

enum class LogPriority : uint32_t {
    UNKNOWN = 0,
    DEFAULT,  // only for minimum_priority().
    VERBOSE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    SILENT,  // only for minimum_priority(); must be last.
};

enum class LogType : uint32_t {
    MIN = 0,
    MAIN = 0,
    RADIO = 1,
    EVENTS = 2,
    SYSTEM = 3,
    CRASH = 4,
    STATS = 5,
    SECURITY = 6,
    KERNEL = 7,
    MAX,
    DEFAULT = 0x7FFFFFFF
};

// 打印格式化字符串日志
void log_print(LogType type, LogPriority priority, const char* tag, const char* fmt, ...)
        __attribute__((__format__(printf, 4, 5)));

}  // namespace autumn
