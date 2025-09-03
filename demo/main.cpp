//
// Created by J Chen on 2023/11/14.
//

#include <thread>
#include <vector>

#include "autumn/log.h"

using namespace autumn;
int main() {
  autumn::LogConfig log_config{"./", 16, 1024, LogType::DEFAULT,
                               LogPriority::DEFAULT};
  logger_t logger = 0;
  create_logger(&logger, log_config);

  std::vector<std::thread> threads;
  for (int i = 0; i < 20; ++i) {
    threads.emplace_back([=]() {
      log_print(logger, LogType::MAIN, LogPriority::VERBOSE, "Network",
                __FILE_NAME__, __LINE__, "%s", "Hello Main!");
      log_print(logger, LogType::RADIO, LogPriority::DEBUG, "Sim",
                __FILE_NAME__, __LINE__, "%s", "Hello Radio!");
      log_print(logger, LogType::SYSTEM, LogPriority::INFO, "Service",
                __FILE_NAME__, __LINE__, "%s", "Hello System!");
      log_print(logger, LogType::SECURITY, LogPriority::WARN, "Hook",
                __FILE_NAME__, __LINE__, "%s", "Hello Security!");
      log_print(logger, LogType::KERNEL, LogPriority::ERROR, "Thread",
                __FILE_NAME__, __LINE__, "%s", "Hello Kernel!");
    });
  }

  log_print(logger, LogType::KERNEL, LogPriority::ERROR, "", "", 0, nullptr);

  for (auto& thread : threads) {
    thread.join();
  }

  destroy_logger(logger);
  return 0;
}
