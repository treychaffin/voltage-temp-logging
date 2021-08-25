#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <vector>

void initSD(bool serialMessages = false);

class DataFile {
private:
    const char* dataFileName;
public:
    DataFile(const char* newDataFileName = "data.txt");
    void createDataFile(bool serialMessages = false);
    void logData(bool serialMessages = false);
};

String logString();