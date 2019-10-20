#pragma once

#if defined(__unix__)
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include <cstdint>
#include <initializer_list>

#include "L1_Peripheral/i2c.hpp"
#include "utility/status.hpp"
#include "utility/units.hpp"

namespace sjsu
{
namespace linux
{
/// An abstract interface for hardware that implements the Inter-integrated
/// Circuit (I2C) or Two Wire Interface (TWI) hardware communication Protocol.
class I2c final : public sjsu::I2c
{
 public:
  constexpr I2c(unsigned i2c_adaptor_number)
      : i2c_adaptor_number_(i2c_adaptor_number)
  {
  }
  virtual Status Initialize() const override
  {
    // Add open i2c device here.
    return Status::kSuccess;
  }
  virtual Status Transaction(Transaction_t transaction) const override
  {

  }

 private:
  unsigned i2c_adaptor_number_;
};
}  // namespace linux
}  // namespace sjsu

#endif  // #if defined(__unix__)