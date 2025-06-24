#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_DRV2605.h>
#include "haptics.h"

Adafruit_DRV2605 drv;
bool haptics_available = false;

// Example patterns: each array can have up to 8 waveforms, ending with 0
const uint8_t pattern_strong_click[] = {1, 0};                // Single strong click
const uint8_t pattern_sharp_click[]  = {2, 0};                // Single sharp click
const uint8_t pattern_ramp_up[]      = {47, 0};               // Single ramp up
const uint8_t pattern_combo[]        = {1, 2, 47, 0};         // Strong, sharp, ramp up
const uint8_t pattern_double_click[] = {1, 1, 0};             // Two strong clicks
const uint8_t pattern_triple_combo[] = {1, 2, 47, 2, 0};      // Strong, sharp, ramp up, sharp
const uint8_t Buzz_1[] = {47, 0};            // Another strong click
const uint8_t pattern_long_buzz[] = {47, 47, 47, 47, 47, 47, 47, 0}; // 7 ramp up buzzes

const uint8_t test_1[] = {52,52,52,52,52,52,52,0};
const uint8_t test_2[] = {51,50,49,48,47,0};
const uint8_t test_3[] = {47, 0, 48, 0, 47, 0, 48, 0};
const uint8_t test_4[] = {47, 0, 70, 0, 48, 0, 70, 0};
const uint8_t test_5[] = {47, 48, 47, 48, 0};
const uint8_t test_6[] = {1, 0, 1, 0, 1, 0, 0};
const uint8_t test_7[] = {83,71,83,71,83,71,0};





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

