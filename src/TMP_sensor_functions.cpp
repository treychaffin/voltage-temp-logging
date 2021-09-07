#include <Arduino.h>
#include "TMP_sensor_functions.hpp"

//******** Temp Sensor Vars *********
RunningStatistics temp_stats;
const float TEMP_SENSOR_SAMPLE_WINDOW = 1;

/*******************************
  Temperature Sensor Functions
********************************/
void initTempSensor(bool serialMessages) {
  temp_stats.setWindowSecs( TEMP_SENSOR_SAMPLE_WINDOW );
  if (serialMessages == true) {Serial.println("Temperature sensor sample window set");}
  pinMode(TEMP_PIN, INPUT);
  if (serialMessages == true) {Serial.println("GPIO initialized: TEMP_PIN");}
}

void sampleTempSensor() {
  int temp_sensor_reading = analogRead(TEMP_PIN);  // read the analog in value:
  temp_stats.input(temp_sensor_reading);  // log to Stats function
}

float readTemp () {
    int sensorreading = temp_stats.mean();
    float sensorvoltage = sensorreading * (AREF / AMAX);
    float sensortempC = (((sensorvoltage * 1000) - 500) / 10);
    return sensortempC;
}