#include <Arduino.h>
#include "sensor_functions.hpp"

//******** AC Voltage Sensing Vars ********
RunningStatistics input_stats;
const float AC_VOLT_FREQUENCY = 60;                                // Line voltage frequency (Hz)
const float AC_VOLT_SAMPLE_WINDOW = 40.0 / AC_VOLT_FREQUENCY;      // How long to average the signal
const int VOLTAGE_LOW_THRESHOLD = 105;

//******** Light Sensor Vars ********
const int LUX_LOW_THRESHOLD = 75;
RunningStatistics light_stats;
const float ANALOG_LIGHT_SENSOR_SAMPLE_WINDOW = 1;                 // How long to average the signal

//********** Calibration Values **********
// see calibration_values.csv for values
const float vbatt_cal = 1.009788;  // 12 VDC battery voltage divider calibration
const float l_cal     = 1;  // analog light sensor calibration
const float slope     = 0.053986;  // AC voltage sensor calibration
const float intercept = -0.255054; // AC voltage sensor calibration

/**********************
    Relay Functions
***********************/

void initGPIO(bool serialMessages) {
  pinMode(AC_PIN, INPUT);
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  pinMode(VBATT_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);
  if (serialMessages == true) {Serial.println("GPIO initialized: AC_PIN, RELAY_PIN, VBATT_PIN, LIGHT PIN, TEMP_PIN");}
}


/*********************************
     Battery Voltage Functions
**********************************/

float getBattVoltageFloat() {
  uint16_t vbatt_raw = getBattVoltageRaw();
  return ((float)vbatt_raw / AMAX * AREF * VBATT_SCALE * vbatt_cal);
}

uint16_t getBattVoltageRaw() {
  return analogRead(VBATT_PIN);
}


/*********************************
    AC Voltage Sensor Functions
**********************************/

void initACVoltageSensor(bool serialMessages) {
  input_stats.setWindowSecs( AC_VOLT_SAMPLE_WINDOW );
  if (serialMessages == true) {Serial.println("AC sensor sample window set");}
}


void sampleACVoltage() {
  int ac_sensor_reading = analogRead(AC_PIN);  // read the analog in value:
  input_stats.input(ac_sensor_reading);  // log to Stats function
}


uint16_t getACVoltage() {
  
  float current_Volts; // Voltage

  current_Volts = intercept + slope * input_stats.sigma(); //Calibartions for offset and amplitude
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


/*****************************
    Light Sensor Functions
******************************/
void initAnalogVoltageSensor(bool serialMessages) {
  light_stats.setWindowSecs( ANALOG_LIGHT_SENSOR_SAMPLE_WINDOW );
  if (serialMessages == true) {Serial.println("Analog light sensor sample window set");}
}

void sampleLuxtoArray() {
  light_stats.input(analogRead(LIGHT_PIN));
}

uint16_t sampleLux() {
  return light_stats.mean() * l_cal;
}

/*******************************
  Temperature Sensor Functions
********************************/

float readTemp () {
    int sensorreading = analogRead(TEMP_PIN);
    float sensorvoltage = sensorreading * (AREF / AMAX);
    float sensortempC = (((sensorvoltage * 1000) - 500) / 10);
    return sensortempC;
}