//
// Created by J Chen on 2022/9/25.
//

#include "autumn/log.h"

#include <cassert>
#include <string>

#include "src/logger.h"
#include "src/utils/inner_log.h"
#include "src/utils/utils.h"

namespace autumn {

char filter_level_to_char(Level level) {
  switch (level) {
    case Level::kVerbose:
      return 'V';
    case Level::kDebug:
      return 'D';
    case Level::kInfo:
      return 'I';
    case Level::kWarn:
      return 'W';
    case Level::kError:
      return 'E';
    case Level::kFatal:
      return 'F';
    case Level::kSilent:
      return 'S';
    case Level::kDefault:
    case Level::kUnknown:
    default:
      return '?';
  }
}

const char* filter_module_to_name(Module module) {
  switch (module) {
    case Module::kMain:
      return "Main";
    case Module::kRadio:
      return "Radio";
    case Module::kSystem:
      return "System";
    case Module::kSecurity:
      return "Security";
    case Module::kKernal:
      return "Kernel";
    case Module::kMin:
    case Module::kMax:
    case Module::kDefault:
    default:
      return "?";
  }
}

int create_logger(logger_t* logger_out, const LogConfig& log_config) {
  assert(!log_config.work_dir.empty());
  assert(log_config.max_files != 0);
  assert(log_config.max_file_size != 0);
  *logger_out = reinterpret_cast<logger_t>(new Logger(log_config));
  return 0;
}

void destroy_logger(logger_t logger) {
  auto* p = reinterpret_cast<Logger*>(logger);
  delete p;
}

void log_print(logger_t logger, Module module, Level level, const char* tag,
               const char* file, uint32_t line, const char* fmt, ...) {
  if (logger == 0) {
    ilog << "logger is nullptr." << end_line;
    return;
  }

  if (!tag || !file || !fmt) {
    ilog << "log print param error." << end_line;
    return;
  }

  std::va_list v;
  va_start(v, fmt);
  std::va_list c;
  char buff[4096] = {};  // TODO(null186): 超过 4096 截断为多条日志。
  std::vsnprintf(buff, 4096, fmt, v);
  va_end(v);

  const LogMessage log_message{filter_module_to_name(module),
                               filter_level_to_char(level),
                               tag,
                               file,
                               line,
                               Utils::ThreadId(),
                               Utils::LocalTimeUs(),
                               buff};
  auto* p = reinterpret_cast<Logger*>(logger);
  p->Print(log_message);
  ilog << "log print format error." << end_line;
}

}  // namespace autumn
