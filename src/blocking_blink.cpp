#include <Arduino.h>
#include "blocking_blink.h"

#define LED_PIN 8

void blocking_blink_setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  delay(1000); // Give time for Serial to connect
}

void blocking_blink_loop() {
  Serial.println("Blocking blink loop running...");
  digitalWrite(LED_PIN, HIGH);  // Turn LED on
  delay(500);                   // Wait 500 ms
  digitalWrite(LED_PIN, LOW);   // Turn LED off
  delay(500);                   // Wait
}