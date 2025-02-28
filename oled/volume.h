#pragma once

#define MAX_VOLUME 100
#define BAR_HEIGHT 12
#define MAX_MAPPED_VOLUME (BAR_HEIGHT * 2)

uint8_t map_volume(uint8_t volume);

void render_volume(void);

void set_volume(uint8_t *data);
