#pragma once

#include "utility/time.hpp"
#include "utility/units.hpp"

namespace sjsu
{
class TimeoutTimer
{
 public:
  TimeoutTimer(std::chrono::nanoseconds timeout) : future_timeout_{ 0 }
  {
    future_timeout_ = Uptime() + timeout;
  }

  std::chrono::nanoseconds GetTimeLeft()
  {
    return future_timeout_ - Uptime();
  }

  void SetTimer(std::chrono::nanoseconds new_timeout)
  {
    future_timeout_ = new_timeout;
  }

 private:
  std::chrono::nanoseconds future_timeout_;
};
}  // namespace sjsu
