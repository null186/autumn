//
// Created by J Chen on 2022/9/25.
//

#include "autumn/log.h"

#include <sys/syscall.h>
#include <unistd.h>

#include <cinttypes>
#include <string>

#include "utils.h"

namespace autumn {

uint64_t get_thread_id() {
    return syscall(SYS_thread_selfid);
}

void log_print(LogType type, LogPriority priority, const char* tag, const char* fmt, ...) {
    va_list v;
    va_start(v, fmt);
    char content[4096];
    int size = vsnprintf(content, 4096, fmt, v);
    char buff[4096];
    snprintf(buff, 4096, "[%s][%d][%d][%s][%" PRIu64 "]%s",
             Utils::ns_to_string(Utils::get_time_ns()).c_str(), type, priority, tag,
             Utils::get_thread_id(), content);
    printf("%s\n", buff);
    va_end(v);
}

}  // namespace autumn
