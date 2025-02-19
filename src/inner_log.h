//
// Created by J Chen on 2023/12/14.
//

#pragma once

#include <cstdint>
#include <iostream>
#include <string>

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
    inline const InnerLog& operator<<(const T& t) const {
        std::cout << t;
        return *this;
    }

  private:
    std::string end_line_;
};

}  // namespace autumn