#include "animation_utils.h"

// current frame
uint8_t current_frame = 0;

// timers
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

void render_animation(int X, int Y, int anim_size, char animation[][anim_size], int anim_frame_duration, int anim_frame_count) { // animation

    oled_set_cursor(X, Y);

    void animation_phase(void) {
        // switch frame
        current_frame = (current_frame + 1) % anim_frame_count;

        // current status
        oled_write_raw_P(animation[abs(1 - current_frame)], anim_size);
    }

    // animation timer
    if(timer_elapsed32(anim_timer) > anim_frame_duration) {
        anim_timer = timer_read32();
        current_wpm = get_current_wpm();
        animation_phase();
    }

    // this fixes the screen on and off bug
    if (current_wpm > 0) {
        oled_on();
        anim_sleep = timer_read32();
    } else if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        oled_off();
    }
}

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (!is_oled_on()) {
            oled_on();
            if (!is_keyboard_master()) {
                uprintf("Slave OLED turned back on\n");
            } else {
                uprintf("Master OLED turned back on\n");
            }
        }
        anim_sleep = timer_read32();
    }
    return true;
} */
