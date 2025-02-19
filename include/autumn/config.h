//
// Created by J Chen on 2023/11/20.
//

#pragma once

#include <string>
#include <utility>

namespace autumn {

enum class AutumnId : uint32_t { NORMAL, EVENT, STATISTICS, DUMP };

/**
 * Autumn log config.
 */
struct LogConfig {
    /** Work dir. */
    const std::string work_dir;
    /** Maximum number of files in a log type directory. */
    const size_t max_files;
    /** Maximum size of a log file. */
    const size_t max_file_size; /* KiB */
    /** {@link LogPriority} values. */
    const LogType type_mask;
    /** {@link LogPriority} values. */
    const LogPriority priority;

    LogConfig(std::string work_dir, const size_t max_files, const size_t max_file_size,
              const LogType type_mask, const LogPriority priority)
        : work_dir(std::move(work_dir)),
          max_files(max_files),
          max_file_size(max_file_size),
          type_mask(type_mask),
          priority(priority) {}
};

/**
 * Autumn event config.
 */
struct EventConfig {};

/**
 * Autumn statistics config.
 */
struct StatisticsConfig {};

/**
 * Autumn dump config.
 */
struct DumpConfig {};

}  // namespace autumn
