#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_DRV2605.h>
#include "haptics.h"

Adafruit_DRV2605 drv;
bool haptics_available = false;

void haptics_setup() {
  // Set custom I2C pins (change 6 and 7 to your actual SDA/SCL pins)
  Wire.begin(6, 7);

  if (!drv.begin()) {
    haptics_available = false;
    return;
  } else {
    haptics_available = true;
  }

  drv.useERM();
  drv.setMode(DRV2605_MODE_INTTRIG);
  drv.selectLibrary(1);
  drv.setWaveform(0, 1);  // Strong click
  drv.setWaveform(1, 2);  // Sharp click
  drv.setWaveform(2, 47); // Ramp up
  drv.setWaveform(3, 0);  // End of sequence
}

// Call this if haptics_available is false
void haptics_retry() {
  haptics_setup();
}

// Call this to trigger the haptic motor every second
void haptics_loop() {
  static unsigned long previousHapticMillis = 0;
  const long hapticInterval = 1000;
  if (!haptics_available) return;

  unsigned long currentMillis = millis();
  if (currentMillis - previousHapticMillis >= hapticInterval) {
    previousHapticMillis = currentMillis;
    drv.go();
  }
}

// Call this to trigger the haptic motor immediately
void haptics_fire() {
  if (haptics_available) {
    drv.go();
  }
}

