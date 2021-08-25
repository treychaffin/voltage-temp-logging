#include "logging.hpp"
#include "gps_functions.hpp"
#include "sensor_functions.hpp"
#include "LED_error.hpp"
#include <iostream>
#include <vector>

void initSD(bool serialMessages) {
    if (!SD.begin(4)) {
        if (serialMessages == true) {Serial.println("SD initialization failed!");}
        while (1) {
            blinkBuiltIn(500,0.25);
        }; // stop the program 
    }
    if (serialMessages == true) {Serial.println("SD initialization done.");}
}

DataFile::DataFile(const char* newDataFileName) : dataFileName(newDataFileName) {
    if (strlen(dataFileName) > 12) {
        Serial.println("Only accepts 8.3 filenames: https://www.arduino.cc/en/Reference/SD");
    }
}
/*********************************************************************************
 * DataFile Constructor
 * Only accepts "short 8.3" filenames. 
 *  Ex: 12345678.123, 20210822.csv, datafile.txt
*********************************************************************************/

void DataFile::createDataFile(bool serialMessages) {
    File file = SD.open(dataFileName, FILE_WRITE);
    if (file) {
        if (serialMessages == true) {Serial.println("File created");}
        file.close();
    } else {
        if (serialMessages == true) {Serial.println("Error creating file");}
    }
}

void DataFile::logData(bool serialMessages) {
    File file = SD.open(dataFileName, FILE_WRITE);
    String dataLogString = logString();
    file.println(dataLogString);
    if (serialMessages == true) {Serial.println(dataLogString);}
    file.close();
}

String logString() {
    String logDelimeter = ",";
    String logString = getTimeAndDateString();
    logString += logDelimeter;
    logString += readTemp();
    logString += logDelimeter;
    logString += getACVoltage();
    logString += logDelimeter;
    logString += sampleLux();
    logString += logDelimeter;
    logString += getBattVoltageFloat();
    return logString;
}