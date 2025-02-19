//
// Created by J Chen on 2022/9/25.
//

#pragma once

#include <sys/cdefs.h>

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <string>

namespace autumn {

struct LogConfig;

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

char filter_pri_to_char(LogPriority pri);

/**
 * TODO: 说明数量不能太多，会影响工作路径下文件个数以及打开的文件数。
 */
enum class LogType : uint32_t {
    MIN = 0,
    MAIN,
    RADIO,
    SYSTEM,
    SECURITY,
    KERNEL,
    MAX,
    DEFAULT = 0x7FFFFFFF
};

std::string filter_type_to_name(LogType type);

typedef long logger_t;

int create_logger(logger_t* logger_out, const LogConfig& log_config);

void destroy_logger(logger_t logger);

// 打印格式化字符串日志
void log_print(logger_t logger, LogType type, LogPriority pri, const char* tag, const char* fun,
               uint32_t line, const char* fmt, ...) __attribute__((__format__(printf, 7, 8)));

// TODO: 记录断言失败，日志级别默认为 FATAL
void log_assert(logger_t logger, const char* condition, const char* tag, const char* fmt, ...)
        __attribute__((__format__(printf, 4, 5)));

// TODO: 在捕获到崩溃信号时调用
void buf_print(int bufID, int priority, const char* tag, const char* fmt, ...)
        __attribute__((__format__(printf, 4, 5)));

int32_t minimum_priority(LogPriority priority);

}  // namespace autumn
