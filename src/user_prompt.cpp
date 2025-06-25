#include <Arduino.h>
#include "user_prompt.h"

uint8_t get_haptic_pattern() {
  Serial.println("Select haptic pattern:");
  Serial.println("1 - Tap");
  Serial.println("2 - Buzz");
  Serial.println("3 - Hum");
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
  Serial.println("2 - Intermediate (5 minutes)");
  Serial.println("3 - Advanced (10 minutes)");
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