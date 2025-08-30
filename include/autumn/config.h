//
// Created by J Chen on 2023/11/20.
//

#ifndef INCLUDE_AUTUMN_CONFIG_H_
#define INCLUDE_AUTUMN_CONFIG_H_

#include <string>
#include <utility>

#include "log.h"

namespace autumn {

/**
 * Autumn log config.
 */
struct LogConfig {
  /** Work dir. */
  std::string work_dir;
  /** Maximum number of files in a log type directory. */
  size_t max_files;
  /** Maximum size of a log file. */
  size_t max_file_size; /* KiB */
  /** {@link LogPriority} values. */
  LogType type_mask;
  /** {@link LogPriority} values. */
  LogPriority priority;
};

}  // namespace autumn

#endif  // INCLUDE_AUTUMN_CONFIG_H_
