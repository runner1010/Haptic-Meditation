#pragma once

extern bool haptics_available;

void haptics_setup();
void haptics_retry();
void trigger_haptic_pattern(uint8_t haptic_type, uint8_t pattern_length);
