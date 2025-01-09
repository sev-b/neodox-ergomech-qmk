// Sets up what the OLED screens display.

#ifdef OLED_ENABLE
#    include "progmem.h"
#    include "status.c"
#    include "animation_utils.c"
#    include "pet.c"
#    include "loop.c"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        defer_exec(3000, pet_animation_phases, NULL);
    }
    else {
        defer_exec(3000, loop_animation_phases, NULL);
    }
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
        render_loop(0, 0);
    }
    return false;
}

#endif
