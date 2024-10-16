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

}

void EmptySPISensor::loop() {

}

void EmptySPISensor::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty SPI sensor");
}

}  // namespace empty_spi_sensor
}  // namespace esphome