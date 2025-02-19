//
// Created by J Chen on 2023/11/20.
//

#pragma once

#include <string>

namespace autumn {

struct LogConfig {
    const std::string work_dir = "/tmp/autumn/log";
    const size_t max_files = 20;
    const size_t max_file_size = 1024;  // KB
};

struct EventConfig {};

struct StatisticsConfig {};

struct DumpConfig {};

}  // namespace autumn

