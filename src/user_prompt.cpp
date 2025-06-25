#include <Arduino.h>
#include "user_prompt.h"

uint8_t get_haptic_pattern() {
  Serial.println("Select haptic pattern:");
  Serial.println("1 - Waveform_1");
  Serial.println("2 - Waveform_2");
  Serial.println("3 - Waveform_3");
  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c >= '1' && c <= '3') {
        Serial.println();
        return c - '0';
      }
    }
  }
}

uint8_t get_pattern_length() {
  Serial.println("Select pattern length:");
  Serial.println("1 - Beginner (2 seconds)");
  Serial.println("2 - Intermediate (4 seconds)");
  Serial.println("3 - Advanced (6 seconds)");
  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c >= '1' && c <= '3') {
        Serial.println();
        return c - '0';
      }
    }
  }
}

uint8_t get_duration() {
  Serial.println("Select duration:");
  Serial.println("1 - Beginner (1 minute)");
  Serial.println("2 - Intermediate (2 minutes)");
  Serial.println("3 - Advanced (3 minutes)");
  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c >= '1' && c <= '3') {
        Serial.println();
        return c - '0';
      }
    }
  }
}

void show_main_prompt() {
  Serial.println("Welcome to Haptic Meditation!");
}