//
// Created by J Chen on 2022/9/25.
//

#pragma once

#include <sys/cdefs.h>

#include <cstdarg>
#include <cstddef>
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
    SILENT,  // must be last.
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

typedef long logger_t;

int create_logger(logger_t* logger_out);

void destroy_logger(logger_t logger);

// 打印格式化字符串日志
void log_print(logger_t logger, LogType type, LogPriority priority, const char* tag,
               const char* fmt, ...) __attribute__((__format__(printf, 5, 6)));

// TODO: 记录断言失败，日志级别默认为 FATAL
void log_assert(logger_t logger, const char* condition, const char* tag, const char* fmt, ...)
        __attribute__((__format__(printf, 4, 5)));

// TODO: 在捕获到崩溃信号时调用
void buf_print(int bufID, int priority, const char* tag, const char* fmt, ...)
        __attribute__((__format__(printf, 4, 5)));

int32_t minimum_priority(LogPriority priority);

}  // namespace autumn
