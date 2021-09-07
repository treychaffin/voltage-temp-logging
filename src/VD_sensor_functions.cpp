#include <Arduino.h>
#include "VD_sensor_functions.hpp"

//********** Calibration Values **********
// see calibration_values.csv for values
const float vbatt_cal = 1;  // 12 VDC battery voltage divider calibration


/*********************************
     Battery Voltage Functions
**********************************/

void initVDsensor(bool serialMessages) {
    pinMode(VBATT_PIN, INPUT);
    if (serialMessages == true) {Serial.println("GPIO initialized: VBATT_PIN");}
}

float getBattVoltageFloat() {
  uint16_t vbatt_raw = getBattVoltageRaw();
  return ((float)vbatt_raw / AMAX * AREF * VBATT_SCALE * vbatt_cal);
}

uint16_t getBattVoltageRaw() {
  return analogRead(VBATT_PIN);
}