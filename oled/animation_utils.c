#include "animation_utils.h"

void render_animation(uint8_t col, uint8_t line, const char (*animation)[OLED_ANIM_SIZE], uint8_t frame, uint8_t rows) {
    for (uint8_t i = 0; i < rows; i++) {
        oled_set_cursor(col, line + i);
        oled_write_raw_P(animation[frame * rows + i], OLED_ANIM_SIZE);
    }
}

uint32_t update_animation_frame(uint8_t *frame, uint8_t max_frames, uint32_t duration) {
    *frame = (*frame + 1) % max_frames;
    return duration;
}
