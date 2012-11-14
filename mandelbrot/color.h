#ifndef _COLOR_H
#define _COLOR_H

#include <stdint.h>

typedef struct {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} pixel_data_t;

void to_rgb(pixel_data_t *pix, double h);
void monochrome(pixel_data_t *pix, double value);
void blue_color(pixel_data_t *pix, double value);

#endif // _COLOR_H
