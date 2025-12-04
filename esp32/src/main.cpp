#include <Arduino.h>
#include <WiFi.h>
#include "config.h"   // provided by the Pi before building

// Define onboard LED pin for ESP32 Dev Module
#ifndef LED_PIN
#define LED_PIN 2   // Most ESP32 dev kits use GPIO 2 for the onboard LED
#endif

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);

  Serial.println("Connecting to WiFi...");
  Serial.println("SSID: " WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected!");
  } else {
    Serial.println("Failed to connect.");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Blink slow if connected
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  } else {
    // Blink fast if NOT connected
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}
