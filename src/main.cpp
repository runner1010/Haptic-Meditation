#include <Arduino.h>
#include "haptics.h"
#include "user_prompt.h"

bool prompt_shown = false;

// Setup
void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }
  haptics_setup();
  delay(10000); // Allow time for the haptics setup to complete
}

//Main Loop
void loop() {
  //initializes variables for haptic feedback
  static uint8_t haptic_pattern = 1;
  static uint8_t pattern_length = 1;
  static uint8_t duration = 1;

  //Checks for haptic connection
  if (!haptics_available) {
    Serial.println("Retrying DRV2605...");
    haptics_retry();
    delay(1000);
    return;
  }

  // Get user input for haptic feedback settings
  if (!prompt_shown) {
    show_main_prompt();
    haptic_pattern = get_haptic_pattern();
    pattern_length = get_pattern_length();
    duration = get_duration();
    prompt_shown = true;
  }

  // Ask user if ready to start
  Serial.println("Ready to start? (y/n)");
  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == 'y' || c == 'Y') {
        // Clear any leftover characters (like newline) from the serial buffer
        while (Serial.available() > 0) Serial.read();

        Serial.println("Press any key to stop early...");
        unsigned long total_time = duration * 60000UL; // duration in minutes to ms
        unsigned long start_time = millis();
        volatile bool stop_flag = false;
        while (millis() - start_time < total_time && !stop_flag) {
            trigger_haptic_pattern(haptic_pattern, pattern_length, &stop_flag);
            if (stop_flag) {
                Serial.println("*******************************");
                Serial.println("Session ended early by user!");
                Serial.println("*******************************");
                break;
            }
        }
        if (!stop_flag) {
            Serial.println("Session complete.");
        }
        prompt_shown = false; // Allow new session
        break;
      } else if (c == 'n' || c == 'N') {
        Serial.println("Cancelled. Restarting prompt.");
        prompt_shown = false;
        break;
      }
    }
  }

  delay(500); // Prevents spamming the prompts
}
