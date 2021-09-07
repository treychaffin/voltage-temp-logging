#include <Arduino.h>
#include "VAC_sensor_functions.hpp"

//********** Calibration Values **********
// see calibration_values.csv for values
const float slope     = 0.046309;  // AC voltage sensor calibration
const float intercept = -0.073526; // AC voltage sensor calibration

//******** AC Voltage Sensing Vars ********
RunningStatistics AC_stats;
const float AC_VOLT_FREQUENCY = 60;                                // Line voltage frequency (Hz)
const float AC_VOLT_SAMPLE_WINDOW = 40.0 / AC_VOLT_FREQUENCY;      // How long to average the signal
const int VOLTAGE_LOW_THRESHOLD = 105;

/*********************************
    AC Voltage Sensor Functions
**********************************/

void initACVoltageSensor(bool serialMessages) {
  AC_stats.setWindowSecs( AC_VOLT_SAMPLE_WINDOW );
  if (serialMessages == true) {Serial.println("AC sensor sample window set");}
  pinMode(AC_PIN, INPUT);
  if (serialMessages == true) {Serial.println("GPIO initialized: AC_PIN");}

}


void sampleACVoltage() {
  int ac_sensor_reading = analogRead(AC_PIN);  // read the analog in value:
  AC_stats.input(ac_sensor_reading);  // log to Stats function
}


uint16_t getACVoltage() {
  
  float current_Volts; // Voltage

  current_Volts = intercept + slope * AC_stats.sigma(); //Calibartions for offset and amplitude
  current_Volts = current_Volts*(40.3231);                //Further calibrations for the amplitude

  // When converting this to an unsigned value, a small errant negative value
  // can make it look like we're reading ends up looking like 65,000-ish volts
  if(current_Volts < 0) {
    current_Volts = 0;
  }
  // Serial.print("AC Volts: ");
  // Serial.println(current_Volts);
  return uint16_t(current_Volts);
}
