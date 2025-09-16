//
// Created by J Chen on 2022/9/25.
//

#ifndef INCLUDE_AUTUMN_LOG_H_
#define INCLUDE_AUTUMN_LOG_H_

#include <string>

#define FALL_V(logger, module, tag, fmt, ...)                              \
  log_print(logger, module, Level::kVerbose, tag, __FILE_NAME__, __LINE__, \
            fmt, ##__VA_ARGS__)
#define FALL_D(logger, module, tag, fmt, ...)                                 \
  log_print(logger, module, Level::kDebug, tag, __FILE_NAME__, __LINE__, fmt, \
            ##__VA_ARGS__)
#define FALL_I(logger, module, tag, fmt, ...)                                \
  log_print(logger, module, Level::kInfo, tag, __FILE_NAME__, __LINE__, fmt, \
            ##__VA_ARGS__)
#define FALL_W(logger, module, tag, fmt, ...)                                \
  log_print(logger, module, Level::kWarn, tag, __FILE_NAME__, __LINE__, fmt, \
            ##__VA_ARGS__)
#define FALL_E(logger, module, tag, fmt, ...)                                 \
  log_print(logger, module, Level::kError, tag, __FILE_NAME__, __LINE__, fmt, \
            ##__VA_ARGS__)
#define FALL_F(logger, module, tag, fmt, ...)                                 \
  log_print(logger, module, Level::kError, tag, __FILE_NAME__, __LINE__, fmt, \
            ##__VA_ARGS__)

namespace autumn {

/**
 * Autumn log level values, in increasing order of level.
 */
enum class Level : uint32_t {
  kUnknown = 0,
  /** The default level, for internal use only. */
  kDefault,
  /** Verbose logging. Should typically be disabled for a release app. */
  kVerbose,
  /** Debug logging. Should typically be disabled for a release app. */
  kDebug,
  /** Informational logging. Should typically be disabled for a release app. */
  kInfo,
  /** Warning logging. For use with recoverable failures. */
  kWarn,
  /** Error logging. For use with unrecoverable failures. */
  kError,
  /** Fatal logging. For use when aborting. */
  kFatal,
  /** For internal use only. Must be last. */
  kSilent,
};

/**
 * Log level to char.
 *
 * @param level
 * @return
 */
char filter_level_to_char(Level level);

/**
 * Here are just a few examples that you can adapt to your use case.
 * The number of module affects the number of folders in the working directory,
 * the total number of files, and the number of open files.
 */
enum class Module : uint32_t {
  kMin = 0,
  kMain = 1 << 0,
  kRadio = 1 << 1,
  kSystem = 1 << 2,
  kSecurity = 1 << 3,
  kKernal = 1 << 4,
  kDefault = kMain | kRadio | kSystem | kSecurity | kKernal,
  kMax = 1 << 30
};

constexpr Module operator&(Module x, Module y) {
  return static_cast<Module>(static_cast<uint32_t>(x) &
                             static_cast<uint32_t>(y));
}

constexpr Module operator|(Module x, Module y) {
  return static_cast<Module>(static_cast<uint32_t>(x) |
                             static_cast<uint32_t>(y));
}

/**
 * Convert LogType to name.
 *
 * @param module
 * @return
 */
std::string filter_module_to_name(Module module);

typedef long logger_t;

/**
 * Autumn log config.
 */
struct LogConfig {
  /** Work dir. */
  std::string work_dir;
  /** Maximum number of files in a log module directory. */
  size_t max_files;
  /** Maximum size of a log file. */
  size_t max_file_size; /* KiB */
  /** {@link Level} values. */
  Module module_mask;
  /** {@link Level} values. */
  Level level;
};

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
 * @param module
 * @param level
 * @param tag
 * @param file
 * @param line
 * @param fmt
 * @param ...
 */
void log_print(logger_t logger, Module module, Level level, const char* tag,
               const char* file, uint32_t line, const char* fmt, ...)
    __attribute__((__format__(printf, 7, 8)));

/**
 * TODO: 记录断言失败，日志级别默认为 kFatal
 *
 * @param logger
 * @param condition
 * @param tag
 * @param fmt
 * @param ...
 */
void log_assert(logger_t logger, const char* condition, const char* tag,
                const char* fmt, ...) __attribute__((__format__(printf, 4, 5)));

/**
 * TODO: 在捕获到崩溃信号时调用
 *
 * @param bufID
 * @param level
 * @param tag
 * @param fmt
 * @param ...
 */
void buf_print(int bufID, int level, const char* tag, const char* fmt, ...)
    __attribute__((__format__(printf, 4, 5)));

}  // namespace autumn

#endif  // INCLUDE_AUTUMN_LOG_H_
