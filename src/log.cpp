//
// Created by J Chen on 2022/9/25.
//

#include "autumn/log.h"

#include <string>

#include "logger.h"
#include "utils.h"

namespace autumn {

int create_logger(logger_t* logger_out) {
    *logger_out = reinterpret_cast<logger_t>(new Logger());
    return 0;
}

void destroy_logger(logger_t logger) {
    auto* p = reinterpret_cast<Logger*>(logger);
    delete p;
}

void log_print(logger_t logger, LogType type, LogPriority priority, const char* tag,
               const char* fmt, ...) {
    if (logger == 0) {
        return;
    }

    Message message;
    message.struct_size = 0;
    message.line = 0;
    message.thread_id = Utils::GetThreadId();
    message.log_type = type;
    message.priority = priority;
    std::string time = Utils::NsToString(Utils::GetLocalTime());
    std::strncpy(message.time, time.c_str(), sizeof(message.time));
    std::strncpy(message.tag, tag, sizeof(message.tag));
    std::strncpy(message.file, "", sizeof(message.file));

    std::va_list v;
    va_start(v, fmt);
    do {
        std::va_list c;
        va_copy(c, v);
        int size = std::vsnprintf(nullptr, 0, fmt, c);
        if (size <= 0) {
            break;
        }
        message.content.resize(size);
        std::vsnprintf(&message.content[0], size, fmt, v);
        auto* p = reinterpret_cast<Logger*>(logger);
        p->Print(message);
    } while (false);
    va_end(v);
}

}  // namespace autumn
