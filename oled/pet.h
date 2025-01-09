#pragma once

// status variables
extern led_t led_usb_state;

void render_pet(uint8_t col, uint8_t line);
uint32_t pet_animation_phases(uint32_t triger_time, void *cb_arg);

