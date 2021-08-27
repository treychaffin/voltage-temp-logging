#include <Arduino.h>
#include "sensor_functions.hpp"
#include "logging.hpp"
#include "LED_error.hpp"
#include "gps_functions.hpp"


// TIMER VARIABLES
uint32_t loopTimerInterval = 60000; // Sets the logging frequency, milli-seconds
uint32_t loopTimer;

// DATA-LOG FILE OBJECT
DataFile logFile("logtest.csv"); // Name file here, MUST USE 8.3 filename


void setup() {
  // wait for serial connection, comment out line to run from non-pc power supply
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
