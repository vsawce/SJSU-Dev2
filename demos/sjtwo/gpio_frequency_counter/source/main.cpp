#include "L1_Peripheral/lpc40xx/gpio.hpp"
#include "L1_Peripheral/hardware_counter.hpp"
#include "L1_Peripheral/frequency_counter.hpp"
#include "L2_HAL/boards/sjtwo.hpp"
#include "utility/time.hpp"
#include "utility/log.hpp"
#include "utility/rtos.hpp"

int main()
{
  LOG_INFO("Gpio Frequency Counter Application Starting...");
  // Create a GPIO to read from. This can be any GPIO that supports GPIO
  // interrupts. On the LPC40xx, that would be pins on port 0 and port 2.
  //
  // Feel free to change this to some other gpio port and pin number.
  sjsu::lpc40xx::Gpio gpio(0, 0);
  // Pass the GPIO above into the gpio counter to be controlled by it.
  // The second parameter allows you to change which event triggers a count.
  // In this case, we want to trigger on rising and falling edges of the pin.
  // Note that this
  sjsu::GpioCounter counter(gpio, sjsu::Gpio::Edge::kEdgeRising);
  // Pass the gpio HardwareCounter object to the frequency counter object to be
  // used to calculate the frequency of the signal on that pin.
  sjsu::FrequencyCounter frequency(&counter);
  // Required: Initialize the hardware.
  frequency.Initialize();
  // Required: Enable the counter.
  frequency.Enable();

  LOG_INFO(
      "With every rising edge of pin P%u.%u, the counter will increase and its "
      "value will be printed to stdout.",
      gpio.GetPin().GetPort(),
      gpio.GetPin().GetPin());

  LOG_INFO(
      "The more rising edges per second on that pin will result in a higher "
      "frequency that is calculated by the frequency counter.");

  while (true)
  {
    // Using printf here to reduce the latency between each
    printf("Freq = %f\n", frequency.GetFrequency().to<double>());
    sjsu::Delay(1000ms - 4ms);
  }
  return 0;
}
