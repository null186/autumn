//
// Created by J Chen on 2023/11/14.
//

#pragma once

#include <cstdint>
#include <string>

#define EXPORT __attribute__((visibility("default")))

namespace autumn {

class Utils {
  public:
    static uint64_t ThreadId();
    static int64_t LocalTimeUs();
    static std::string FormattedSTime();
};

}  // namespace autumn
