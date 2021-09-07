#include <Arduino.h>
#include "AL_sensor_functions.hpp"
#include "TMP_sensor_functions.hpp"
#include "VAC_sensor_functions.hpp"
#include "VD_sensor_functions.hpp"
#include "logging.hpp"
#include "gps_functions.hpp"


// TIMER VARIABLES
uint32_t loopTimerInterval = 10000; // Sets the logging frequency, milli-seconds
uint32_t loopTimer;

// DATA-LOG FILE OBJECT
DataFile logFile("longtest.csv"); // Name file here, MUST USE 8.3 filename


void setup() {
  // wait for serial connection, comment out line to run from non-pc power supply
  // while (!Serial); 

  Serial.begin(115200);

  Serial.println("*************************************");
  Serial.println("   AC voltage / temperature logger   ");
  Serial.println("*************************************");
  Serial.println("");
  initSD(true);
  initVDsensor(true);
  initAnalogLightSensor(true);
  initACVoltageSensor(true);
  initTempSensor(true);
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
  sampleAnalogLightSensor();
  sampleTempSensor();
  if (millis() - loopTimer > loopTimerInterval) {
    loopTimer = millis();
    logFile.logData(true);
  }
}
