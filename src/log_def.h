//
// Created by J Chen on 2025/9/3.
//

#ifndef SRC_LOG_DEF_H_
#define SRC_LOG_DEF_H_

#include <string>

namespace autumn {

struct SourceLoc {
  /** Optional filename, may be set to nullptr. */
  const char* file{};
  /** Optional function, ignore if file is nullptr. */
  const char* fun{};
  /** Optional line number, ignore if file is nullptr. */
  int32_t line = 0;
};

struct LogMessage {
  /** The time for the log message. */
  int64_t time = 0;
  /** The thread ID for the log message. */
  int64_t thread_id = 0;
  /** The log level char. */
  char level = '?';
  /** The log module name. */
  const char* module{};
  /** The tag for the log message. */
  const char* tag{};
  /** The log source location. */
  SourceLoc loc{};
  /** The log message itself. */
  const char* msg{};
};

struct LogEntry {
  /** The log module name. */
  char module[16] = {};
  /** The log entry itself. */
  std::string entry{};
};

}  // namespace autumn

#endif  // SRC_LOG_DEF_H_
