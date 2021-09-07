#include <Arduino.h>
#include <Filters.h>

#define AC_PIN A0

//******** AC Voltage Sensing Vars ********
extern const float AC_VOLT_FREQUENCY;
extern const float AC_VOLT_SAMPLE_WINDOW;
extern const int VOLTAGE_LOW_THRESHOLD;

/*********************************
    AC Voltage Sensor Functions
**********************************/

void initACVoltageSensor(bool serialMessages = false);
void sampleACVoltage();
uint16_t getACVoltage();