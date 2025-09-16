//
// Created by J Chen on 2025/9/3.
//

#ifndef SRC_LOG_DEF_H_
#define SRC_LOG_DEF_H_

#include <string>

namespace autumn {

struct LogMessage {
  /** The log module name. */
  const char* module;
  /** The log level char. */
  char level = '?';
  /** The tag for the log message. */
  const char* tag;
  /** Optional filename, may be set to nullptr. */
  const char* file;
  /** Optional line number, ignore if file is nullptr. */
  uint32_t line = 0;
  /** The thread ID for the log message. */
  uint64_t thread_id = 0;
  /** The time for the log message. */
  int64_t time;
  /** The log message itself. */
  const char* formatted;
};

struct LogEntry {
  /** The log module name. */
  char module[16] = {};
  /** The log entry itself. */
  std::string entry{};
};

}  // namespace autumn

#endif  // SRC_LOG_DEF_H_
