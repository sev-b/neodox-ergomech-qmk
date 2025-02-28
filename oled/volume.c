#include "volume.h"
#include <math.h>
#include "print.h"

uint8_t current_volume = 0;

void set_volume(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case 0:
        {
            if (*value_data >= 0 && *value_data <= 100) {
                current_volume = *value_data;
                uprintf("Volume set to: %d\n", current_volume); // Debugging output
            }
            else
                print("Received volume value out of range"); // Debugging output
            break;
        }
        default:
        {
            print("Received value id incorrect"); // Debugging output
            break;
        }
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    uprintf("Received data: command_id=%d, channel_id=%d, value_data=%d\n", *command_id, *channel_id, value_id_and_data[1]); // Debugging output

    if ( *channel_id == id_custom_channel ) {
        print("Received *channel_id == id_custom_channel"); // Debugging output
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                set_volume(value_id_and_data);
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }
    *command_id = id_unhandled;
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uprintf("raw_hid_receive_kb called with data[0]=%d\n", data[0]); // Debugging output
    uint8_t *command_id = &(data[0]);

    // Due to an older version of via.c in Vial that does not support
    // id_custom_set/get_value, we use id_handled to invoke via_custom_value_command_kb.
    if (*command_id == id_unhandled) {
        via_custom_value_command_kb(&data[1], length - 1);
    }
}

uint8_t map_volume(uint8_t volume) {
    double slope = (double)MAX_MAPPED_VOLUME / MAX_VOLUME;
    return round(slope * volume);
}

void render_volume(void) {
    uint8_t mapped_volume = MAX_MAPPED_VOLUME - map_volume(current_volume); // 24-0

    oled_set_cursor(0, 1);
    oled_write(" VOL ", false);

    // Draw the vertical bar
    for (uint8_t i = 0; i < BAR_HEIGHT; i++) {
        char bar[] = {0x00};
        if (mapped_volume < i * 2 + 1) {
            bar[0] = (i == 0) ? 0x98 : (i == BAR_HEIGHT - 1) ? 0x99 : 0x04;
        } else if (mapped_volume == i * 2 + 1) {
            bar[0] = (i == 0) ? 0x09 : (i == BAR_HEIGHT - 1) ? 0x0A : 0x9A;
        } else {
            bar[0] = (i == 0) ? 0x01 : (i == BAR_HEIGHT - 1) ? 0x02 : 0x03;
        }
        oled_set_cursor(3, 3 + i);
        oled_write_P(bar, false);
    }
    oled_set_cursor(0, 3 + mapped_volume / 2);
    oled_write(get_u8_str(current_volume, ' '), false);
}
