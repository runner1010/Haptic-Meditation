#include <Arduino.h>
#include "blink.h"
#include "haptics.h"
#include "blocking_blink.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for Serial to connect (needed for some boards)
  haptics_setup();    // Uncomment the following line to run haptics

  /********** For debugging purposes **********/
  // blink_setup();    // Uncomment the following line to setup blinking
  // blocking_blink_setup(); // Uncomment the following line to blocking blink
}

void loop() {
  // Uncomment the following line to run haptics
  if (!haptics_available) {
    Serial.println("Retrying DRV2605...");
    haptics_retry();
    delay(1000); // Wait before retrying again
  }

  // This is to run haptics in a loop
  haptics_loop();

//   // This is to trigger haptics with user input
//   if (Serial.available() > 0) {
//     char c = Serial.read();
//     if (c == ' ') {
//       Serial.println("Spacebar pressed! Firing haptics sequence...");
//       haptics_fire();
//     }
//   }

  /********** For debugging purposes **********/
  // Uncomment the following line to blocking blink
  // blocking_blink_loop();

  // Uncomment the following lines to blink without blocking
  // blink_loop();
  // Serial.println(get_led_state() ? "LED ON" : "LED OFF");
  // delay(500);

  delay(1000);
}