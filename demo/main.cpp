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

    log_print(logger, LogType::SYSTEM, LogPriority::DEBUG, tag, "%s", content);

    destroy_logger(logger);
    return 0;
}
