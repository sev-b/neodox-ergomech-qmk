#include "status.h"

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
    uint8_t current_wpm = get_current_wpm();
    if (current_wpm < 10)
        sprintf(buf, "WPM %d", current_wpm);
    else if (current_wpm < 100)
        sprintf(buf, "W  %d", current_wpm);
    else
        sprintf(buf, "W %d", current_wpm);
    oled_set_cursor(0, 9);
    oled_write_ln(buf, false);
}
