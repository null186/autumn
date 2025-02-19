//
// Created by J Chen on 2023/12/17.
//

#include "format_task.h"

#include <cinttypes>

#include "inner_log.h"

namespace autumn {

void FormatTask::Start() {
    ilog << params_.message << end_line;

    char buff[4096] = {0};  // TODO: 超过 4096 截断为多条日志。
    std::snprintf(buff, 4096, "[%s][%" PRIu64 "][%c][%s][%s][%s][%d] %s\n", params_.time,
                  params_.thread_id, params_.priority, params_.type, params_.tag, params_.file,
                  params_.line, params_.message.c_str());

    LogEntry log_entry;
    memcpy(log_entry.type, params_.type, sizeof(log_entry.type));
    log_entry.entry = std::string(buff);
    BusinessTask<LogMessage, LogEntry>::TaskSuccess(log_entry);
}

void FormatTask::Finish() {}

}  // namespace autumn
