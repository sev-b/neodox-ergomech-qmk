#pragma once

#include <stdint.h>
#include "oled_driver.h"

#define OLED_ANIM_SIZE (32 + 1)
#define OLED_ANIM_MAX_FRAMES 8

void render_animation(uint8_t col, uint8_t line, const char (*animation)[OLED_ANIM_SIZE], uint8_t frame, uint8_t rows);
uint32_t update_animation_frame(uint8_t *frame, uint8_t max_frames, uint32_t duration);
