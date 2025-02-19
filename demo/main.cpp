//
// Created by J Chen on 2023/11/14.
//

#include "autumn/log.h"

using namespace autumn;
int main() {
    const char* tag = "Test";
    const char* content = "Hello World!";
    log_print(LogType::MAIN, LogPriority::DEBUG, tag, "%s", content);
    return 0;
}
