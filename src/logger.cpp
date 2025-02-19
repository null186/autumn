//
// Created by J Chen on 2023/11/20.
//

#include "logger.h"

#include <cinttypes>

#include "utils.h"

namespace autumn {

autumn::Logger::Logger() = default;

autumn::Logger::~Logger() = default;

void autumn::Logger::Print(Message message) {
    char buff[4096] = {0};
    std::snprintf(buff, 4096, "[%s][%d][%" PRIu64 "][%s][%s][%d] %s", message.time,
                  message.log_type, message.thread_id, message.tag, message.file, message.line,
                  message.content.c_str());
    printf("%s\n", buff);
}

}  // namespace autumn
