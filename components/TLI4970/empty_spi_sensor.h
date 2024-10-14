#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace empty_spi_sensor {

class TLI4970Component : public PollingComponent, public Sensor {

 public:
  void setup() override {
    // Initialize the SPI communication
    SPI.begin();
    pinMode(cs_pin_, OUTPUT);
    digitalWrite(cs_pin_, HIGH);  // Ensure the CS pin is high when idle
  }

 void update() override {
    // Begin communication with the TLI4970 sensor
    digitalWrite(cs_pin_, LOW);  // Select the sensor
    delayMicroseconds(1);        // Small delay for stability

    uint16_t sensor_data = SPI.transfer16(0x0000);  // Read the data from the sensor
    digitalWrite(cs_pin_, HIGH); // Deselect the sensor

    float current_value = parse_current(sensor_data);

    // Publish the current sensor value to ESPHome
    ESP_LOGD("TLI4970", "Current: %.2f A", current_value);
    publish_state(current_value);
  }

  void loop() override;
  void dump_config() override;

 private:
  int cs_pin_;

  float parse_current(uint16_t data) {
    // Extract the current value from the 12-bit data (based on TLI4970 documentation)
    return static_cast<float>(data & 0x0FFF) * 0.1;  // Convert the raw data to current in Amps
  }

};  //class

}  // namespace empty_spi_sensor
}  // namespace esphome