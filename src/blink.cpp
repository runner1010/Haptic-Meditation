#include <Arduino.h>
#include "blink.h"

#define LED_PIN 8

unsigned long previousLedMillis = 0;
const long ledInterval = 500;
bool ledState = false;

void blink_setup() {
  pinMode(LED_PIN, OUTPUT);
}

void blink_loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousLedMillis >= ledInterval) {
    previousLedMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? LOW : HIGH);
  }
}

bool get_led_state() {
  return ledState;
}