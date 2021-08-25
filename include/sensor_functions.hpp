#include <Arduino.h>
#include <Filters.h>

#define AC_PIN A0
#define RELAY_PIN A1 // Set the relay pin
#define VBATT_PIN A2 // Set battery voltage sample pin
#define LIGHT_PIN A3 // Set photosensor sample pin
#define TEMP_PIN A4 // Set the temperature sensor pin

#define VBATT_R1 45.3 // High side battery voltage divider in kOhms
#define VBATT_R2 12.4 // Low side battery voltage divider in kOhms
// Multiply raw voltage by this scale factor to get the actual battery voltage
#define VBATT_SCALE ((VBATT_R1 + VBATT_R2) / VBATT_R2)  

#define AREF 3.3 // Analog reference voltage
#define AMAX 1023.0 // Maximum analog value

//******** AC Voltage Sensing Vars ********
extern const float AC_VOLT_FREQUENCY;
extern const float AC_VOLT_SAMPLE_WINDOW;
extern const int VOLTAGE_LOW_THRESHOLD;

//******** Light Sensor Vars ********
extern const int LUX_LOW_THRESHOLD;

/**********************
     GPIO Functions
***********************/

void initGPIO(bool serialMessages = false);

/*********************************
    AC Voltage Sensor Functions
**********************************/

void initACVoltageSensor(bool serialMessages = false);
void sampleACVoltage();
uint16_t getACVoltage();

/*********************************
    Voltage Divider Functions
**********************************/

uint16_t getBattVoltageRaw();
float getBattVoltageFloat();

/*****************************
    Light Sensor Functions
******************************/

void initAnalogVoltageSensor(bool serialMessages = false);
void sampleLuxtoArray();
uint16_t sampleLux();

/********************************
    Temperature Sensor Functions
*********************************/

float readTemp();