/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
