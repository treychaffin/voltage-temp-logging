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

DataFile logFile("logtest.csv"); // MUST USE 8.3 filename


bool secFlag = false;

void setup() {
  while (!Serial);  
  Serial.begin(115200);
  Serial.println("*************************************");
  Serial.println("   AC voltage / temperature logger   ");
  Serial.println("*************************************");
  Serial.println("");
  initSD(true);
  initGPIO(true);
  initAnalogVoltageSensor(true);
  initACVoltageSensor(true);
  logFile.createDataFile(true);
  initGPS(true);
  Serial.print("logging will begin in ");
  Serial.print(loopTimerInterval/1000);
  Serial.println(" seconds");
  loopTimer = millis();
}

void loop() {
  readGPS();
  sampleACVoltage();
  sampleLuxtoArray();
  if (millis() - loopTimer > loopTimerInterval) {
    loopTimer = millis();
    logFile.logData(true);
  }
}
