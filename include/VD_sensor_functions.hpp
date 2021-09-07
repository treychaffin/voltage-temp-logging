#include <Arduino.h>
#include <Filters.h>

#define RELAY_PIN A1 // Set the relay pin
#define VBATT_PIN A2 // Set battery voltage sample pin


#define VBATT_R1 45.3 // High side battery voltage divider in kOhms
#define VBATT_R2 12.4 // Low side battery voltage divider in kOhms
// Multiply raw voltage by this scale factor to get the actual battery voltage
#define VBATT_SCALE ((VBATT_R1 + VBATT_R2) / VBATT_R2)  

#define AREF 3.3 // Analog reference voltage
#define AMAX 1023.0 // Maximum analog value


/*********************************
    Voltage Divider Functions
**********************************/

void initVDsensor(bool serialMessages = false);
uint16_t getBattVoltageRaw();
float getBattVoltageFloat();