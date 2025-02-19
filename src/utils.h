//
// Created by J Chen on 2023/11/14.
//

#pragma once

#include <cstdint>
#include <string>

namespace autumn {

class Utils {
  public:
    static uint64_t GetThreadId();
    static int64_t GetLocalTime();
    static std::string NsToString(int64_t time);
};

}  // namespace autumn
