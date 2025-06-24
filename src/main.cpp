#include <Arduino.h>
#include "haptics.h"

bool prompt_shown = false;

unsigned long get_duration_from_user() {
  String input = "";
  Serial.println("Enter duration in seconds (e.g., 10):");
  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {
        if (input.length() > 0) break;
      } else if (isDigit(c)) {
        input += c;
        Serial.print(c); // Echo back
      }
    }
  }
  Serial.println();
  return input.toInt() * 1000UL; // Convert seconds to milliseconds
}

void loop_haptics_with_interrupt(unsigned long duration_ms) {
  // Clear any leftover characters before starting
  while (Serial.available() > 0) Serial.read();

  unsigned long start = millis();
  Serial.println("Haptics running. Press any key to stop early.");
  while (millis() - start < duration_ms) {
    haptics_fire();
    delay(50);

    if (Serial.available() > 0) {
      while (Serial.available() > 0) Serial.read();
      Serial.println("Haptics interrupted by user.");
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }
  haptics_setup();
}

void loop() {
  if (!haptics_available) {
    Serial.println("Retrying DRV2605...");
    haptics_retry();
    delay(1000);
    return;
  }

  if (!prompt_shown) {
    Serial.println("Enter a haptic sequence to run (1-6), or 'L' for a long looped haptic:");
    prompt_shown = true;
  }

  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input >= '1' && input <= '6') {
      uint8_t pattern_id = input - '0';
      haptics_set_pattern(pattern_id);
      haptics_fire();
      prompt_shown = false;
    } else if (input == 'L' || input == 'l') {
      haptics_set_pattern(1); // Example: use pattern 1 for looping
      unsigned long duration = get_duration_from_user();
      loop_haptics_with_interrupt(duration);
      prompt_shown = false;
    }
    while (Serial.available() > 0) Serial.read();
  }

  delay(500);
}
