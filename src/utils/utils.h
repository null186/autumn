//
// Created by J Chen on 2023/11/14.
//

#ifndef SRC_UTILS_UTILS_H_
#define SRC_UTILS_UTILS_H_

#include <cstdint>
#include <string>

#define EXPORT __attribute__((visibility("default")))
#define UNUSED __attribute__((unused))
#ifdef AUTUMN_DEBUG
#define DEBUG_UNUSED __attribute__((unused))
#else
#define DEBUG_UNUSED
#endif

namespace autumn {

class Utils {
 public:
  static uint64_t ThreadId();
  static int64_t LocalTimeUs();
  static std::string FormattedSTime();
};

}  // namespace autumn

#endif  // SRC_UTILS_UTILS_H_
