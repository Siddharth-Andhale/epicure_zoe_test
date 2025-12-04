#include <Arduino.h>

void setup() {
  pinMode(2, OUTPUT);  // Built-in LED on many ESP32 dev boards
}

void loop() {
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
