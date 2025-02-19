//
// Created by J Chen on 2023/11/14.
//

#pragma once

#include <cstdint>
#include <string>

namespace autumn {

class Utils {
  public:
    static uint64_t get_thread_id();
    static uint64_t get_time_ns();
    static std::string ns_to_string(uint64_t ns);
};

}  // namespace autumn
