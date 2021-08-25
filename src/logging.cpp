#include "logging.hpp"
#include "gps_functions.hpp"
#include "sensor_functions.hpp"
#include "LED_error.hpp"
#include <iostream>
#include <vector>

void initSD() {
    if (!SD.begin(4)) {
        Serial.println("SD initialization failed!");
        while (1) {
            blinkBuiltIn(500,0.25);
        }; // stop the program 
    }
    Serial.println("SD initialization done.");
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

void DataFile::createDataFile() {
    File file = SD.open(dataFileName, FILE_WRITE);
    if (file) {
        Serial.println("File created");
        file.close();
    } else {
        Serial.println("Error creating file");
    }
}

void DataFile::logData() {
    Serial.println(logString());
}

String logString() {
    String logDelimeter = ",";
    String logString = getTimeAndDateString();
    logString += logDelimeter;
    logString += readTemp();
    logString += logDelimeter;
    logString += sampleLux();
    logString += logDelimeter;
    logString += getBattVoltageFloat();
    return logString;
}