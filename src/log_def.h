//
// Created by J Chen on 2025/9/3.
//

#ifndef SRC_LOG_DEF_H_
#define SRC_LOG_DEF_H_

#include <string>

namespace autumn {

struct LogMessage {
  /** Must be set to sizeof(LogMessage) and is used for versioning. */
  size_t struct_size = 0;
  /** Optional line number, ignore if file is nullptr. */
  uint32_t line = 0;
  /** The thread ID for the log message. */
  uint64_t thread_id = 0;
  /** The log priority char. */
  char priority = '?';
  /** The tag for the log message. */
  char tag[16] = {};
  /** Optional function name, may be set to nullptr. */
  char file[16] = {};
  /** The log type name. */
  char type[16] = {};
  /** The time for the log message. */
  char time[32] = {};
  /** The log message itself. */
  std::string message{};
};

struct LogEntry {
  /** The log type name. */
  char type[16] = {};
  /** The log entry itself. */
  std::string entry{};
};

}  // namespace autumn

#endif  // SRC_LOG_DEF_H_
