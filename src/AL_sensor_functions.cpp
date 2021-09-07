#include <Arduino.h>
#include "AL_sensor_functions.hpp"

//********** Calibration Values **********
// see calibration_values.csv for values
const float l_cal     = 1;  // analog light sensor calibration

//******** Light Sensor Vars ********
const int LUX_LOW_THRESHOLD = 75;
RunningStatistics light_stats;
const float ANALOG_LIGHT_SENSOR_SAMPLE_WINDOW = 1;  // How long to average the signal

/*****************************
    Light Sensor Functions
******************************/

/**
 * \brief Initialize Analog (Light) Voltage Sensor. 
 * 
 * Sets the "ANALOG_LIGHT_SENSOR_SAMPLE_WINDOW" to the float 
 * defined in "Light Sensor Vars" section. 
 * For Serial Messages: call "true" when calling the function 
 * 
 * \param serialMessages boolean value, defaults to false
 *
 * \return None
 */
void initAnalogLightSensor(bool serialMessages) {
  light_stats.setWindowSecs( ANALOG_LIGHT_SENSOR_SAMPLE_WINDOW );
  if (serialMessages == true) {Serial.println("Analog light sensor sample window set");}
  pinMode(LIGHT_PIN, INPUT);
  if (serialMessages == true) {Serial.println("GPIO initialized: LIGHT PIN");}
}

void sampleAnalogLightSensor() {
  light_stats.input(analogRead(LIGHT_PIN));
}

uint16_t sampleAnalogLight() {
  return light_stats.mean() * l_cal;
}