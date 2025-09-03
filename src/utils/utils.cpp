//
// Created by J Chen on 2023/11/14.
//

#include "src/utils/utils.h"

#if defined(__ANDROID__)
//
#elif defined(_WIN32)
//
#elif defined(__APPLE__)
#include <sys/syscall.h>
#include <unistd.h>
#elif defined(__linux)
//
#endif

static constexpr int64_t kSecondsToMicroseconds = 1000 * 1000;

uint64_t autumn::Utils::ThreadId() {
#if defined(__ANDROID__)
  //
#elif defined(_WIN32)
  //
#elif defined(__APPLE__)
  return syscall(SYS_thread_selfid);
#elif defined(__linux)
  //
#endif
}

int64_t autumn::Utils::LocalTimeUs() {
  return std::chrono::duration_cast<std::chrono::microseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

inline struct tm* local_time(const time_t* time, struct tm* result) {
  return localtime_r(time, result);
}

std::string autumn::Utils::FormattedSTime() {
  char buff[32] = {0};
  const std::time_t t = LocalTimeUs() / kSecondsToMicroseconds;
  struct std::tm tm{};
  local_time(&t, &tm);
  std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &tm);
  return buff;
}
