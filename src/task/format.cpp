//
// Created by J Chen on 2023/12/17.
//

#include "format.h"

#include <cinttypes>

#include "src/utils/inner_log.h"

namespace autumn {

void FormatTask::Run(const LogMessage& in) {
  ilog << in.msg << end_line;

  const auto time = Utils::FormattedSTime(in.time);

  char buff[4096] = {};  // TODO(null186): 超过 4096 截断为多条日志。
  std::snprintf(buff, 4096, "[%s][%" PRIu64 "][%c][%s][%s][%s][%s][%d] %s\n",
                time.c_str(), in.thread_id, in.level, in.module, in.tag,
                in.loc.file, in.loc.fun, in.loc.line, in.msg);

  LogEntry log_entry;
  memcpy(log_entry.module, in.module, sizeof(log_entry.module));
  log_entry.entry = std::string(buff);
  NextSuccess(log_entry);
}

void FormatTask::Finish(const LogEntry& out) {}

}  // namespace autumn
