# Voltage/Temperature logging experiment

Attempting to find a correlation between temperature and the analog readings obtained from the ZMPT101B AC voltage sensor module

## hardware

* ZMPT101B AC voltage sensor module
* Adafruit Feather M0 Adalogger
* MicroSD Card
* Adafruit Feather Ultimate GPS FeatherWing
* Adafruit ALS-PT19 Analog Light Sensor Breakout
* Voltage Divider (for measuring 12VDC battery)
    * Hot side resistor: 45.3 kOhms
    * Low side resistor: 12.4 kOhms

## description

This program logs a csv file to the attached sd card.

Columns are logged as follows:

GPSDATE(UTC) GPSTIME(UTC) | Temperature Reading | Analog Light Sensor Reading | 12 VDC Battery Voltage
------------------------- |-------------------------------------------------- | ----------------------