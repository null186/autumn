//
// Created by J Chen on 2023/12/17.
//

#include "format.h"

#include <cinttypes>

#include "src/utils/inner_log.h"

namespace autumn {

void FormatTask::Run() {
  ilog << params_.message << end_line;

  char buff[4096] = {};  // TODO(null186): 超过 4096 截断为多条日志。
  std::snprintf(buff, 4096, "[%s][%" PRIu64 "][%c][%s][%s][%s][%d] %s\n",
                params_.time, params_.thread_id, params_.level, params_.module,
                params_.tag, params_.file, params_.line,
                params_.message.c_str());

  LogEntry log_entry;
  memcpy(log_entry.module, params_.module, sizeof(log_entry.module));
  log_entry.entry = std::string(buff);
  Success(log_entry);
}

void FormatTask::Finish(const LogEntry& param) {}

}  // namespace autumn
