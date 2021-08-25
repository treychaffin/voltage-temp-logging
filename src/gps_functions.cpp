#include "gps_functions.hpp"

Adafruit_GPS GPS(&GPSSerial);

uint32_t timer = millis();



void initGPS(bool serialMessages) {
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPSSerial.println(PMTK_Q_RELEASE);
  bool satFlag = false;
  while (getSatellites() == 0 && getYear() == 0) {
    readGPS();
    if (satFlag == false && serialMessages == true) {
      Serial.println("waiting for GPS satellites... ");
      satFlag = true;
    }
    delay(100);
  }
  if (serialMessages == true) {Serial.println("successful GPS satellite connection");}
}

void readGPS() {
  GPS.read();
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())) 
      return;
  }
  
}

void printGPS() {
  if (millis() - timer > 2000) {
    timer = millis();
    Serial.print("\nTime: ");
    if (GPS.hour < 10) { Serial.print('0'); }
    Serial.print(GPS.hour, DEC); Serial.print(':');
    if (GPS.minute < 10) { Serial.print('0'); }
    Serial.print(GPS.minute, DEC); Serial.print(':');
    if (GPS.seconds < 10) { Serial.print('0'); }
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    if (GPS.milliseconds < 10) {
      Serial.print("00");
    } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
}

int getSatellites() {
  return (int)GPS.satellites;
}

String getISO8601DateString() {
  String datestr;
  datestr += "20";
  datestr += GPS.year;
  datestr += "-";
  if (GPS.month < 10) {datestr += "0";}
  datestr += GPS.month;
  datestr += "-";
  if (GPS.day < 10) {datestr += "0";}
  datestr += GPS.day;
  return datestr;
}

String getTimeString() {
  String timestr;
  if (GPS.hour < 10) {timestr += "0";}
  timestr += GPS.hour;
  timestr += ":";
  if (GPS.minute < 10) {timestr += "0";}
  timestr += GPS.minute;
  timestr += ":";
  if (GPS.seconds < 10) {timestr += "0";}
  timestr += GPS.seconds;
  return timestr;
}

String getTimeAndDateString() {
  String TimeAndDateString;
  TimeAndDateString += getISO8601DateString();
  TimeAndDateString += " ";
  TimeAndDateString += getTimeString();
  return TimeAndDateString;
}

String getSecondsString() {
  return String(GPS.seconds);
}

uint8_t getSeconds() {
  return GPS.seconds;
}

uint8_t getMinute() {
  return GPS.minute;
}

uint8_t getHour() {
  return GPS.hour;
}

uint8_t getDay() {
  return GPS.day;
}

uint8_t getMonth() {
  return GPS.month;
}

uint8_t getYear() {
  return GPS.year;
}