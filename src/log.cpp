//
// Created by J Chen on 2022/9/25.
//

#include "autumn/log.h"

#include <cassert>
#include <string>

#include "autumn/config.h"
#include "logger.h"
#include "utils/inner_log.h"
#include "utils/utils.h"

namespace autumn {

char filter_pri_to_char(LogPriority pri) {
  switch (pri) {
    case LogPriority::VERBOSE:
      return 'V';
    case LogPriority::DEBUG:
      return 'D';
    case LogPriority::INFO:
      return 'I';
    case LogPriority::WARN:
      return 'W';
    case LogPriority::ERROR:
      return 'E';
    case LogPriority::FATAL:
      return 'F';
    case LogPriority::SILENT:
      return 'S';
    case LogPriority::DEFAULT:
    case LogPriority::UNKNOWN:
    default:
      return '?';
  }
}

std::string filter_type_to_name(LogType type) {
  switch (type) {
    case LogType::MAIN:
      return "Main";
    case LogType::RADIO:
      return "Radio";
    case LogType::SYSTEM:
      return "System";
    case LogType::SECURITY:
      return "Security";
    case LogType::KERNEL:
      return "Kernel";
    case LogType::MIN:
    case LogType::MAX:
    case LogType::DEFAULT:
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

void log_print(logger_t logger, LogType type, LogPriority pri, const char* tag,
               const char* file, uint32_t line, const char* fmt, ...) {
  if (logger == 0) {
    ilog << "logger is nullptr." << end_line;
    return;
  }

  if (!tag || !file || !fmt) {
    ilog << "log print param error." << end_line;
    return;
  }

  LogMessage log_message;
  log_message.struct_size = 0;
  log_message.line = line;
  log_message.thread_id = Utils::ThreadId();
  log_message.priority = filter_pri_to_char(pri);
  std::strncpy(log_message.tag, tag, sizeof(log_message.tag));
  std::strncpy(log_message.file, file, sizeof(log_message.file));
  std::string type_name = filter_type_to_name(type);
  std::strncpy(log_message.type, type_name.c_str(), sizeof(log_message.type));
  std::string time = Utils::FormattedSTime();
  std::strncpy(log_message.time, time.c_str(), sizeof(log_message.time));

  std::va_list v;
  va_start(v, fmt);
  std::va_list c;
  va_copy(c, v);
  int size = std::vsnprintf(nullptr, 0, fmt, c);
  if (size > 0) {
    log_message.message.resize(size + 1);
    std::vsnprintf(&log_message.message[0], size + 1, fmt, v);
    auto* p = reinterpret_cast<Logger*>(logger);
    p->Print(log_message);
  }
  ilog << "log print format error." << end_line;
  va_end(v);
}

}  // namespace autumn
