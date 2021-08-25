#include <Arduino.h>
#include <iostream>
#include <RTClib.h>
#include "sensor_functions.hpp"
#include "logging.hpp"
#include "LED_error.hpp"
#include "gps_functions.hpp"

uint32_t loopTimer;
uint32_t loopTimerInterval = 60000; // milli-seconds
uint8_t topOfMinute = 0;

DataFile logFile("logtest.csv");


bool secFlag = false;

void setup() {
  while (!Serial);  
  Serial.begin(115200);
  initGPIO();
  initAnalogVoltageSensor();
  initACVoltageSensor();
  logFile.createDataFile();
  Serial.println("GPS TEST");
  initGPS(true);
  Serial.println("begin logging");
  loopTimer = millis();
}

void loop() {
  readGPS();
  sampleACVoltage();
  sampleLuxtoArray();
  if (millis() - loopTimer > loopTimerInterval) {
    loopTimer = millis();
    logFile.logData();
  }
}
