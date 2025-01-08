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
#    include "animation_utils.c"
#    include "luna.c"
#    include "superloop.c"

int current_wpm = 0;

void render_status_modern(void) {
    oled_set_cursor(0, 1);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.caps_lock ? PSTR("CPS\07\10") : PSTR("CPS\05\06"), false);
    oled_set_cursor(0, 3);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_ALT ? PSTR("ALT\07\10") : PSTR("ALT\05\06"), false);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL ? PSTR("CTL\07\10") : PSTR("CTL\05\06"), false);
    oled_write_P(get_highest_layer(layer_state) == 1 ? PSTR("FUN\07\10") : PSTR("FUN\05\06"), false);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT ? PSTR("SFT\07\10") : PSTR("SFT\05\06"), false);
    oled_write_P((get_mods() | get_oneshot_mods()) & MOD_MASK_GUI ? PSTR("WIN\07\10") : PSTR("WIN\05\06"), false);

    char buf[16];
    if (current_wpm < 10)
        sprintf(buf, "WPM %d", current_wpm);
    else if (current_wpm < 100)
        sprintf(buf, "W  %d", current_wpm);
    else
        sprintf(buf, "W %d", current_wpm);
    oled_set_cursor(0, 9);
    oled_write_ln(buf, false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    /*  if (is_keyboard_master()) {
         return OLED_ROTATION_270;
     } */
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    // oled_clear();
    current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        render_status_modern();
        led_usb_state = host_keyboard_led_state();
        render_luna(0, 13);
    } else {
        render_loop();
    }
    return false;
}

#endif
