#include "arduino_secrets.h";
#include "soilMoistureSensor.h";

const int loopDelay = 5 * 1000;
const int adcResolution = 12; //bits
const int dataRate = 9600;
int adcMaxVal = (pow(2, adcResolution) - 1);

#include "thingProperties.h"

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(dataRate);
  delay(1500);
  
  setupAnalog();

  // Defined in thingProperties.h
  initProperties();
  
  initSoilMoistureSensor(adcResolution);

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  setSoilState();
  delay(loopDelay);
}

void setupAnalog() {
  analogReadResolution(adcResolution);
}
void setSoilState() {
  
  humidity_value = readAnalog_soilMoistureValue();
  
  moisture_percentage = (100 - ((humidity_value / adcMaxVal) * 100));
  
  if(humidity_value > 0 && humidity_value < dry_soil_threshold) {
    dry_soil = true;
    humid_soil = false;
    in_water = false;
  } else if(humidity_value >= dry_soil_threshold && humidity_value < humid_soil_threshold) {
    dry_soil = false;
    humid_soil = true;
    in_water = false;
  } else {
    dry_soil = false;
    humid_soil = false;
    in_water = true;
  }
}