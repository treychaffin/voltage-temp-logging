#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <vector>

void initSD();

class DataFile {
private:
    const char* dataFileName;
public:
    DataFile(const char* newDataFileName = "data.txt");
    void createDataFile();
    void logData();
};

String logString();