#include <Arduino.h>
#include <Adafruit_GPS.h>
#define GPSSerial Serial1



void initGPS(bool serialMessages = false);
void readGPS();
void printGPS();
int getSatellites();
String getISO8601DateString();
String getTimeString();
String getTimeAndDateString();
String getSecondsString();
uint8_t getSeconds();
uint8_t getYear();