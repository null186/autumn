//
// Created by J Chen on 2023/12/14.
//

#ifndef SRC_UTILS_INNER_LOG_H_
#define SRC_UTILS_INNER_LOG_H_

#include <cstdint>
#include <iostream>
#include <string>

#include "utils.h"

#define ilog InnerLog::GetInstance()
#define end_line InnerLog::GetInstance().GetEnd()

namespace autumn {

class InnerLog {
 public:
  InnerLog() { end_line_ = "\n"; }
  virtual ~InnerLog() = default;

 public:
  inline std::string GetEnd() const { return end_line_; }

  static InnerLog GetInstance() {
    static InnerLog INSTANCE;
    return INSTANCE;
  }

  template <typename T>
  inline const InnerLog& operator<<(const T& t DEBUG_UNUSED) const {
#ifdef AUTUMN_DEBUG
    std::cout << t;
#endif
    return *this;
  }

 private:
  std::string end_line_;
};

}  // namespace autumn

#endif  // SRC_UTILS_INNER_LOG_H_
