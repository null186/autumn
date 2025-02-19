//
// Created by J Chen on 2023/11/14.
//

#include "autumn/log.h"

using namespace autumn;
int main() {
    const char* tag = "Test";
    const char* content = "Hello World!";

    logger_t logger = 0;
    create_logger(&logger);

    log_print(logger, LogType::MAIN, LogPriority::UNKNOWN, tag, "%s", content);
    log_print(logger, LogType::RADIO, LogPriority::DEFAULT, tag, "%s", content);
    log_print(logger, LogType::EVENTS, LogPriority::VERBOSE, tag, "%s", content);
    log_print(logger, LogType::SYSTEM, LogPriority::DEBUG, tag, "%s", content);
    log_print(logger, LogType::CRASH, LogPriority::INFO, tag, "%s", content);
    log_print(logger, LogType::STATS, LogPriority::WARN, tag, "%s", content);
    log_print(logger, LogType::SECURITY, LogPriority::ERROR, tag, "%s", content);
    log_print(logger, LogType::KERNEL, LogPriority::FATAL, tag, "%s", content);

    destroy_logger(logger);
    return 0;
}
