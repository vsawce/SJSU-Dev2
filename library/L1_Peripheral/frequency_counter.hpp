#pragma once

#include "utility/units.hpp"
#include "utility/time.hpp"
#include "L1_Peripheral/hardware_counter.hpp"

namespace sjsu
{
class FrequencyCounter
{
 public:
  FrequencyCounter(HardwareCounter * counter) : counter_(counter) {}

  virtual void Initialize()
  {
    counter_->Initialize();
    counter_->SetDirection(HardwareCounter::Direction::kUp);
  }

  virtual void Enable()
  {
    counter_->Enable();
    previous_time_ = Uptime();
  }

  virtual void Disable()
  {
    counter_->Disable();
  }

  virtual void Reset()
  {
    previous_count_ = counter_->GetCount();
    previous_time_  = Uptime();
  }

  virtual units::frequency::hertz_t GetFrequency()
  {
    uint32_t count_delta = counter_->GetCount() - previous_count_;
    units::time::microsecond_t time_delta = Uptime() - previous_time_;
    units::frequency::hertz_t result      = count_delta / time_delta;
    Reset();
    return result;
  }

 private:
  HardwareCounter * counter_;
  uint32_t previous_count_                 = 0;
  std::chrono::microseconds previous_time_ = 0us;
};
}  // namespace sjsu
