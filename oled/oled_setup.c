// Sets up what the OLED screens display.

#if defined(OLED_ENABLE) && OLED_ENABLE
#include "progmem.h"
#include "status.c"
#include "animation_utils.c"
#include "pet.c"
    #if defined(RAW_ENABLE) && RAW_ENABLE
    #include "volume.c"
    #else
    #include "loop.c"
    #endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        defer_exec(3000, pet_animation_phases, NULL);
    }
    #if !defined(RAW_ENABLE) || !RAW_ENABLE
    else if (loop_animation_phases) {
        defer_exec(3000, loop_animation_phases, NULL);
    }
    #endif
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (last_input_activity_elapsed() > 30000) {
        oled_off();
        return false;
    } else {
        oled_on();
    }
    if (is_keyboard_master()) {
        render_status_modern();
        render_pet(0, 13);
    } else {
        #if defined(RAW_ENABLE) && RAW_ENABLE
        render_volume();
        #else
        render_loop(0,0);
        #endif
    }
    return false;
}

#endif
