#include "esphome/core/log.h"
#include "empty_spi_sensor.h"

namespace esphome {
namespace empty_spi_sensor {

static const char *TAG = "empty_spi_sensor.sensor";

void EmptySPISensor::setup() {
    // Initialize the SPI communication
    SPI.begin();
    pinMode(cs_pin_, OUTPUT);
    digitalWrite(cs_pin_, HIGH);  // Ensure the CS pin is high when idle

}

void EmptySPISensor::update() {
    // Begin communication with the TLI4970 sensor
    digitalWrite(cs_pin_, LOW);  // Select the sensor
    delayMicroseconds(1);        // Small delay for stability

    uint16_t sensor_data = SPI.transfer16(0x0000);  // Read the data from the sensor
    digitalWrite(cs_pin_, HIGH); // Deselect the sensor
    ESP_LOGD("TLI4970", "Readout 16 bits: 0x%x A", sensor_data);
    float current_value = parse_current(sensor_data);

    // Publish the current sensor value to ESPHome
    ESP_LOGD("TLI4970", "Current: %.2f A", current_value);
    publish_state(current_value);

}

void EmptySPISensor::loop() {

}

void EmptySPISensor::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty SPI sensor");
}

}  // namespace empty_spi_sensor
}  // namespace esphome