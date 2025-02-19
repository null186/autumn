//
// Created by J Chen on 2023/11/20.
//

#pragma once

#include <string>
#include <utility>

namespace autumn {

enum class AutumnId : uint32_t { NORMAL, EVENT, STATISTICS, DUMP };

struct LogConfig {
    const std::string work_dir;
    const size_t max_files;
    const size_t max_file_size;  // KB
    const LogType type_mask;
    const LogPriority priority;

    LogConfig(std::string work_dir, const size_t max_files, const size_t max_file_size,
              const LogType type_mask, const LogPriority priority)
        : work_dir(std::move(work_dir)),
          max_files(max_files),
          max_file_size(max_file_size),
          type_mask(type_mask),
          priority(priority) {}
};

struct EventConfig {};

struct StatisticsConfig {};

struct DumpConfig {};

}  // namespace autumn
