#include "color.h"

#include <math.h>

void to_rgb(pixel_data_t *pix, double h) {
	double s = 1, v = 1;
	double var_h = h * 6;
	double var_i = floor( var_h );
	double var_1 = v * ( 1 - s );
	double var_2 = v * ( 1 - s * ( var_h - var_i ) );
	double var_3 = v * ( 1 - s * ( 1 - ( var_h - var_i ) ) );

	if      ( var_i == 0 ) { pix->red = v*255     ; pix->green = var_3*255 ; pix->blue = var_1*255; }
	else if ( var_i == 1 ) { pix->red = var_2*255 ; pix->green = v*255     ; pix->blue = var_1*255; }
	else if ( var_i == 2 ) { pix->red = var_1*255 ; pix->green = v*255     ; pix->blue = var_3*255; }
	else if ( var_i == 3 ) { pix->red = var_1*255 ; pix->green = var_2*255 ; pix->blue = v*255;     }
	else if ( var_i == 4 ) { pix->red = var_3*255 ; pix->green = var_1*255 ; pix->blue = v*255;     }
	else                   { pix->red = v*255     ; pix->green = var_1*255 ; pix->blue = var_2*255; }
}

void monochrome(pixel_data_t *pix, double value) {
	pix->red = value * 255;
	pix->green = value * 255;
	pix->blue = value * 255;
}

void blue_color(pixel_data_t *pix, double value) {
	int c = (int)(value * 255);
	pix->red = (c<128)?c/2:64+(c-128)*3/2;
	pix->blue = (c<64)?c*4:255-(c-64)*4/3;
	pix->green = (pix->blue/2+pix->red/2+c/4);
}

