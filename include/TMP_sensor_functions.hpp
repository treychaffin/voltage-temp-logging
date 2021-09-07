#include <Arduino.h>
#include <Filters.h>

#define TEMP_PIN A4 // Set the temperature sensor pin

#define AREF 3.3 // Analog reference voltage
#define AMAX 1023.0 // Maximum analog value

/********************************
    Temperature Sensor Functions
*********************************/

void initTempSensor(bool serialMessages = false);
void sampleTempSensor();
float readTemp();