//
// Created by J Chen on 2022/9/25.
//

#include "autumn/log.h"

#include <string>

#include "logger.h"
#include "utils.h"

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

int create_logger(logger_t* logger_out) {
    *logger_out = reinterpret_cast<logger_t>(new Logger());
    return 0;
}

void destroy_logger(logger_t logger) {
    auto* p = reinterpret_cast<Logger*>(logger);
    delete p;
}

void log_print(logger_t logger, LogType type, LogPriority pri, const char* tag, const char* file,
               uint32_t line, const char* fmt, ...) {
    if (logger == 0) {
        return;
    }

    Message message;
    message.struct_size = 0;
    message.line = line;
    message.thread_id = Utils::ThreadId();
    message.priority = filter_pri_to_char(pri);
    std::strncpy(message.tag, tag, sizeof(message.tag));
    std::strncpy(message.file, file, sizeof(message.file));
    std::string type_name = filter_type_to_name(type);
    std::strncpy(message.type, type_name.c_str(), sizeof(message.type));
    std::string time = Utils::FormattedSTime();
    std::strncpy(message.time, time.c_str(), sizeof(message.time));

    std::va_list v;
    va_start(v, fmt);
    do {
        std::va_list c;
        va_copy(c, v);
        int size = std::vsnprintf(nullptr, 0, fmt, c);
        if (size <= 0) {
            break;
        }
        message.content.resize(size + 1);
        std::vsnprintf(&message.content[0], size + 1, fmt, v);
        auto* p = reinterpret_cast<Logger*>(logger);
        p->Print(message);
    } while (false);
    va_end(v);
}

}  // namespace autumn
