#include "bitmap.h"
#include "mandelbrot.h"

#include <math.h>
#include <stdlib.h>


int punkt_iteration(double cx, double cy, double max_betrag_quadrat, int max_iterations) {
	double betrag_quadrat = 0;
	int iter = 0;
	double x = 0, y = 0;

	while ((betrag_quadrat <= max_betrag_quadrat) && (iter < max_iterations)) {
		double x2 = x * x - y * y + cx;
		double y2 = 2 * x * y + cy;
		x = x2;
		y = y2;
		iter++;
		betrag_quadrat = x * x + y * y;
	}

	return iter;
}

double smooth_punkt_iteration(double cx, double cy, double max_betrag_quadrat, int max_iterations) {
	double betrag_quadrat = 0;
	int iter = 0;
	double x = 0, y = 0;

	while ((betrag_quadrat <= max_betrag_quadrat) && (iter < max_iterations)) {
		double x2 = x * x - y * y + cx;
		double y2 = 2 * x * y + cy;
		x = x2;
		y = y2;
		iter++;
		betrag_quadrat = x * x + y * y;
	}

	double B = 5;
	double P = 2;

	return iter + (log(2 * log(B)) - log(log(abs(betrag_quadrat)))) / log(P);
}


void calc_mandelbrot(pixel_data_t *data, int full_width, int full_height,
                     int clip_x, int clip_y, int clip_width, int clip_height) {
	double center_x = CENTER_X;
	double center_y = CENTER_Y;
	double domain_width = DOMAIN_WIDTH;

	double domain_height = domain_width * full_height / full_width;
	double min_cx = center_x - domain_width / 2;
	double min_cy = center_y - domain_height / 2;
	double scale = domain_width / full_width;

	int x; int y;
    for (x=clip_x; x<clip_x+clip_width; x++) {
        for (y=clip_y; y<clip_y+clip_height; y++) {
			double cx = min_cx + x*scale;
			double cy = min_cy + y*scale;

			double i = punkt_iteration(cx, cy, 2, MAX_ITERATIONS);

			pixel_data_t pixel = {0, 0, 0};
			if (i < MAX_ITERATIONS)
				to_rgb(&pixel, i / MAX_ITERATIONS);

			data[(y-clip_y)*clip_width + (x-clip_x)] = pixel;
		}
	}
}
