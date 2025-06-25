#pragma once

uint8_t get_haptic_pattern();         // 1-tap, 2-buzz, 3-hum
uint8_t get_pattern_length();      // 1-beginner, 2-intermediate, 3-advanced
uint8_t get_duration();      // 1-beginner, 2-intermediate, 3-advanced
void show_main_prompt();