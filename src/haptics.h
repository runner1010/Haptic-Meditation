#pragma once

extern bool haptics_available;

void haptics_setup();
void haptics_loop();
void haptics_retry();
void haptics_fire();
void haptics_set_pattern(uint8_t pattern_id);