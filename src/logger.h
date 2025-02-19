//
// Created by J Chen on 2023/11/20.
//

#pragma once

#include <cstdint>
#include <cstdio>
#include <string>

#include "autumn/log.h"

namespace autumn {

struct Message {
    /* Must be set to sizeof(Message) and is used for versioning. */
    size_t struct_size = 0;
    /* Optional line number, ignore if file is nullptr. */
    uint32_t line = 0;
    /* The thread ID for the log message. */
    uint64_t thread_id = 0;
    /* {@link LogType} values. */
    LogType log_type = LogType::DEFAULT;
    /* {@link LogPriority} values. */
    LogPriority priority = LogPriority::DEFAULT;
    /* The tag for the log message. */
    char tag[16] = {};  // TODO: 超出则截断。
    /* Optional file name, may be set to nullptr. */
    char file[16] = {};  // TODO: 超出则截断。
    /* The time for the log message. */
    char time[32] = {};
    /* The log message itself. */
    std::string content{};
};

class Logger {
  public:
    Logger();

    virtual ~Logger();

  public:
    void Print(Message message);

  private:
    //

  private:
    //
};

}  // namespace autumn
