#include "esp32-hal-gpio.h";

const int soil_moisture_digital_IN = 2;
const int soil_moisture_analog_IN = A0;

const float dry_soil_percentage_threshold = 0.3;
const float humid_soil_percentage_threshold = 0.75;

float dry_soil_threshold;
float humid_soil_threshold;

void calculateThresholds(int adcResolution) {
  int adcMaxValue = pow(2, adcResolution) - 1;
  dry_soil_threshold = adcMaxValue * dry_soil_percentage_threshold;
  humid_soil_threshold = adcMaxValue * humid_soil_percentage_threshold;
}

void initSoilMoistureSensor(int adcResolution) {
  pinMode(soil_moisture_digital_IN, INPUT);
  pinMode(soil_moisture_analog_IN, INPUT);
  
  calculateThresholds(adcResolution);
}

int readDigital_soilMoistureValue() {
  return digitalRead(soil_moisture_digital_IN);
}

int readAnalog_soilMoistureValue() {
  return analogRead(soil_moisture_analog_IN);
}