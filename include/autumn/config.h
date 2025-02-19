//
// Created by J Chen on 2023/11/20.
//

#pragma once

#include <string>
#include <utility>

namespace autumn {

enum class MainType : uint32_t { NORMAL, EVENT, STATISTICS, DUMP };

struct LogConfig {
    const std::string work_dir;
    const size_t max_files;
    const size_t max_file_size;  // KB

    LogConfig(std::string work_dir, const size_t max_files, const size_t max_file_size)
        : work_dir(std::move(work_dir)), max_files(max_files), max_file_size(max_file_size) {}
};

struct EventConfig {};

struct StatisticsConfig {};

struct DumpConfig {};

}  // namespace autumn
