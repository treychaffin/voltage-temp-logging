#include <Arduino.h>
#include "relay_functions.hpp"

/**********************
    Relay Functions
***********************/

void initRelay(bool serialMessages) {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  if (serialMessages == true) {Serial.println("GPIO initialized: RELAY_PIN");}
}