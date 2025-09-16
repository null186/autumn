//
// Created by J Chen on 2023/11/14.
//

#include <thread>
#include <vector>

#include "autumn/log.h"

using namespace autumn;

int main() {
  const LogConfig log_config{"./autumn", 16, 1024, Module::kDefault,
                             Level::kDefault};
  logger_t logger = 0;
  create_logger(&logger, log_config);

  std::vector<std::thread> threads;
  for (int i = 0; i < 20; ++i) {
    threads.emplace_back([=]() {
      FALL_V(logger, Module::kMain, "Network", "%s", "Hello Main!");
      FALL_D(logger, Module::kRadio, "Sim", "%s", "Hello Radio!");
      FALL_I(logger, Module::kSystem, "Service", "%s", "Hello System!");
      FALL_W(logger, Module::kSecurity, "Hook", "%s", "Hello Security!");
      FALL_E(logger, Module::kKernal, "Thread", "%s", "Hello Kernel!");
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  destroy_logger(logger);
  return 0;
}
