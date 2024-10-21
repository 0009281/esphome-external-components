#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/spi/spi.h"
#include "esphome/core/defines.h"

#define TLI4970_CURRENT_OFFSET		4096
#define TLI4970_CURRENT_DIVIDER		80.0

namespace esphome {
namespace empty_spi_sensor {

class EmptySPISensor : public sensor::Sensor,
                       public PollingComponent,
                       public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING,
                                            spi::DATA_RATE_1KHZ> {

 public:

  EmptySPISensor(int cs_pin) : PollingComponent(1000), cs_pin_(cs_pin) {}
  void setup() override;

  void update() override;

  void loop() override;
  void dump_config() override;

 private:
  int cs_pin_;

  float parse_current(uint16_t data) {
    // Extract the current value from the 12-bit data (based on TLI4970 documentation)
    //return static_cast<float>(data & 0x0FFF) * 0.1;  // Convert the raw data to current in Amps
     return static_cast<float>(data & - TLI4970_CURRENT_OFFSET)  / TLI4970_CURRENT_DIVIDER;  // Convert the raw data to current in Amps
  }

};  //class

}  // namespace empty_spi_sensor
}  // namespace esphome