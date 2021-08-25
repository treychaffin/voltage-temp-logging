#include <Arduino.h>

void initLEDBuiltIn();
void blinkBuiltIn(int milliSecondsPeriod, double pulseWidthOnRatio);
void blinkBuiltInLoop(int numBlinks, int blinkDelay, int afterLoopDelay);
void blinkIncreasingFrequency(int milliSecondsPerPeriod, int freqGain, int afterLoopDelay);
