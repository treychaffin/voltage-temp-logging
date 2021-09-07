#include <Arduino.h>
#include <Filters.h>

#define LIGHT_PIN A3 // Set photosensor sample pin

//******** Light Sensor Vars ********
extern const int LUX_LOW_THRESHOLD;

/*****************************
    Light Sensor Functions
******************************/

void initAnalogLightSensor(bool serialMessages = false);
void sampleAnalogLightSensor();
uint16_t sampleAnalogLight();