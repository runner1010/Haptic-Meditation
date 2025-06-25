#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_DRV2605.h>
#include "haptics.h"
#include <math.h>

Adafruit_DRV2605 drv;
bool haptics_available = false;

//Haptic Feedback Type
const uint8_t Waveform_1[] = {17,0}; //Strong Click
const uint8_t Waveform_2[] = {24,0};  //Sharp Tick
const uint8_t Waveform_3[] = {4,0}; //Sharp Click

// Minimum allowed delay between triggers
const float MIN_DELAY_MS = 10.0;

//Setup Connection to DRV2605
void haptics_setup() {
  Wire.begin(6, 7); // Set I2C pins (SDA/SCL pins)

  if (!drv.begin()) {
    haptics_available = false;
    return;
  } else {
    haptics_available = true;
  }

  drv.useERM();
  drv.setMode(DRV2605_MODE_INTTRIG);
  drv.selectLibrary(1);
}

// Call this if haptics_available is false
void haptics_retry() {
  haptics_setup();
}


void trigger_haptic_pattern(uint8_t haptic_type, uint8_t pattern_length, volatile bool* stop_flag) {
    // Initialize the DRV2605 waveform 
    const uint8_t* pattern = nullptr;
    if (haptic_type == 1) {
        pattern = Waveform_1;
    } else if (haptic_type == 2) {
        pattern = Waveform_2;
    } else if (haptic_type == 3) {
        pattern = Waveform_3;
    } else {
        pattern = Waveform_1; // Default
    }
    // Set up to 8 waveforms (DRV2605 supports 8 slots)
    for (uint8_t i = 0; i < 8; i++) {
        drv.setWaveform(i, pattern[i]);
        if (pattern[i] == 0) break; // End of sequence
    }

    // Define ramp steps based on pattern_length (1=short, 2=medium, 3=long)
    uint8_t steps = 0;
    switch (pattern_length) {
        case 1: steps = 10; break; // Beginner
        case 2: steps = 20; break; // Intermediate
        case 3: steps = 40; break; // Advanced
        default: steps = 10; break;
    }

    float start_delay = 1000.0; // ms
    float end_delay = 50.0;     // ms

    // Ramp up (logarithmic)
    Serial.println("Ramp up...");
    for (uint8_t i = 0; i < steps; i++) {
        if (*stop_flag) return;
        float ratio = (float)i / (steps - 1);
        float delay_ms = start_delay * pow(end_delay / start_delay, ratio);
        if (delay_ms < MIN_DELAY_MS) delay_ms = MIN_DELAY_MS;
        drv.go();
        unsigned long t0 = millis();
        while (millis() - t0 < (unsigned long)delay_ms) {
            if (Serial.available() > 0) {
                Serial.read();
                *stop_flag = true;
                return;
            }
        }
    }

    // Pause
    Serial.println("Pause...");
    unsigned long pause_time = (unsigned long)(steps * start_delay / 2);
    unsigned long pause_start = millis();
    while (millis() - pause_start < pause_time) {
        if (Serial.available() > 0) {
            Serial.read();
            *stop_flag = true;
            return;
        }
    }

    // Ramp down (logarithmic)
    Serial.println("Ramp down...");
    for (uint8_t i = 0; i < steps; i++) {
        if (*stop_flag) return;
        float ratio = (float)i / (steps - 1);
        float delay_ms = end_delay * pow(start_delay / end_delay, ratio);
        if (delay_ms < MIN_DELAY_MS) delay_ms = MIN_DELAY_MS;
        drv.go();
        unsigned long t0 = millis();
        while (millis() - t0 < (unsigned long)delay_ms) {
            if (Serial.available() > 0) {
                Serial.read();
                *stop_flag = true;
                return;
            }
        }
    }

    // Pause
    Serial.println("Pause...");
    pause_start = millis();
    while (millis() - pause_start < pause_time) {
        if (Serial.available() > 0) {
            Serial.read();
            *stop_flag = true;
            return;
        }
    }
}

