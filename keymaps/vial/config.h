/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C
/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS
#define VIAL_KEYBOARD_UID {0x54, 0xB9, 0x18, 0x3D, 0xE9, 0x29, 0xA8, 0x22}
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

#define OLED_FONT_H "../oled/oled_font.c"

#define SPLIT_ACTIVITY_ENABLE
// #define SPLIT_WPM_ENABLE
