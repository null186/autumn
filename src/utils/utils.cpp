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

namespace autumn {

int64_t Utils::ThreadId() {
  thread_local int64_t thread_id = 0;
  if (thread_id == 0) {
#if defined(__ANDROID__)
    //
#elif defined(_WIN32)
    //
#elif defined(__APPLE__)
    thread_id = syscall(SYS_thread_selfid);
#elif defined(__linux)
    //
#endif
  }
  return thread_id;
}

int64_t Utils::LocalTimeUs() {
  const auto d = std::chrono::system_clock::now().time_since_epoch();
  const auto ms = std::chrono::duration_cast<std::chrono::microseconds>(d);
  return ms.count();
}

inline tm* local_time(const time_t* time, tm* result) {
  return localtime_r(time, result);
}

std::string Utils::FormattedSTime(const int64_t time) {
  const auto du_us = std::chrono::microseconds(time);
  const auto du_s = std::chrono::duration_cast<std::chrono::seconds>(du_us);
  const auto us = (du_us - du_s).count();

  const std::time_t t = du_s.count();
  std::tm tm{};
  local_time(&t, &tm);

  char buff[32] = {};
  const auto len = std::strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", &tm);
  snprintf(buff + len, sizeof(buff) - len, ".%06lld", us);
  return buff;
}

}  // namespace autumn
