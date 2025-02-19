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

/**
 * Autumn log priority values, in increasing order of priority.
 */
enum class LogPriority : uint32_t {
    UNKNOWN = 0,
    /** The default priority, for internal use only. */
    DEFAULT,
    /** Verbose logging. Should typically be disabled for a release app. */
    VERBOSE,
    /** Debug logging. Should typically be disabled for a release app. */
    DEBUG,
    /** Informational logging. Should typically be disabled for a release app. */
    INFO,
    /** Warning logging. For use with recoverable failures. */
    WARN,
    /** Error logging. For use with unrecoverable failures. */
    ERROR,
    /** Fatal logging. For use when aborting. */
    FATAL,
    /** For internal use only. Must be last. */
    SILENT,
};

/**
 * Log priority to char.
 *
 * @param pri
 * @return
 */
char filter_pri_to_char(LogPriority pri);

/**
 * Here are just a few examples that you can adapt to your use case.
 * The number of type affects the number of folders in the working directory, the total number of
 * files, and the number of open files.
 */
enum class LogType : uint32_t {
    MIN = 0,
    MAIN = 1 << 0,
    RADIO = 1 << 1,
    SYSTEM = 1 << 2,
    SECURITY = 1 << 3,
    KERNEL = 1 << 4,
    DEFAULT = MAIN | RADIO | SYSTEM | SECURITY | KERNEL,
    MAX = 1 << 30
};

inline constexpr LogType operator&(LogType x, LogType y) {
    return static_cast<LogType>(static_cast<uint32_t>(x) & static_cast<uint32_t>(y));
}

inline constexpr LogType operator|(LogType x, LogType y) {
    return static_cast<LogType>(static_cast<uint32_t>(x) | static_cast<uint32_t>(y));
}

/**
 * Convert LogType to name.
 *
 * @param type
 * @return
 */
std::string filter_type_to_name(LogType type);

typedef long logger_t;

/**
 * Create logger.
 *
 * @param logger_out
 * @param log_config
 * @return
 */
int create_logger(logger_t* logger_out, const LogConfig& log_config);

/**
 * Destroy logger.
 *
 * @param logger
 */
void destroy_logger(logger_t logger);

/**
 * Print log.
 *
 * @param logger
 * @param type
 * @param pri
 * @param tag
 * @param fun
 * @param line
 * @param fmt
 * @param ...
 */
void log_print(logger_t logger, LogType type, LogPriority pri, const char* tag, const char* fun,
               uint32_t line, const char* fmt, ...) __attribute__((__format__(printf, 7, 8)));

/**
 * TODO: 记录断言失败，日志级别默认为 FATAL
 *
 * @param logger
 * @param condition
 * @param tag
 * @param fmt
 * @param ...
 */
void log_assert(logger_t logger, const char* condition, const char* tag, const char* fmt, ...)
        __attribute__((__format__(printf, 4, 5)));

/**
 * TODO: 在捕获到崩溃信号时调用
 *
 * @param bufID
 * @param priority
 * @param tag
 * @param fmt
 * @param ...
 */
void buf_print(int bufID, int priority, const char* tag, const char* fmt, ...)
        __attribute__((__format__(printf, 4, 5)));

}  // namespace autumn
