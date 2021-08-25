#include <Arduino.h>
#include "LED_error.hpp"

void initLEDBuiltIn() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void blinkBuiltIn(int milliSecondsPeriod, double pulseWidthOnRatio) {
    int onDelay = (int)round(milliSecondsPeriod * pulseWidthOnRatio);
    int offDelay = (int)round(milliSecondsPeriod - (milliSecondsPeriod * pulseWidthOnRatio));
    digitalWrite(LED_BUILTIN,HIGH);
    delay(onDelay);
    digitalWrite(LED_BUILTIN,LOW);
    delay(offDelay);
}


void blinkBuiltInLoop(int numBlinks, int blinkDelay, int afterLoopDelay) {
    for (int i = 0; i < numBlinks; i++) {
        digitalWrite(LED_BUILTIN,HIGH);
        delay(blinkDelay);
        digitalWrite(LED_BUILTIN,LOW);
        delay(blinkDelay);
    }
    delay(afterLoopDelay);
}

void blinkIncreasingFrequency(int milliSecondsPerPeriod, int freqGain, int afterLoopDelay) {
    for (int blinkDelay = milliSecondsPerPeriod / 2; blinkDelay > 1; blinkDelay -= freqGain) {
        digitalWrite(LED_BUILTIN,HIGH);
        delay(blinkDelay);
        digitalWrite(LED_BUILTIN,LOW);
        delay(blinkDelay);
    }
    digitalWrite(LED_BUILTIN,HIGH);
    delay(afterLoopDelay);
}