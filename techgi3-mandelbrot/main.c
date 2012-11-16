#include "bitmap.h"
#include "mandelbrot.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define WIDTH  3200
#define HEIGHT 2400

int main(int argc, char** argv) {
	int return_code = EXIT_FAILURE;
	unsigned long start, end;
	char *filename;

	if (argc != 2) {
		printf("Usage: mandelbrot BMPFILE\n");
		return return_code;
	}
	filename = argv[1];

	/* Gr��e des gesamten, zu erzeugenden Bildes festlegen */
	int width = WIDTH, height = HEIGHT;

	/* Puffer f�r Bilddaten allokieren */
	pixel_data_t *data = calloc(width*height, sizeof(pixel_data_t));
	if (data) {

		/* Neue Ausgabedatei erstellen und zum Schreiben �ffnen */
		FILE *file = fopen(filename, "wb");
		if (file) {

			/* BMP-Header schreiben */
			write_bitmap_header(file, width, height);

			/* Startzeit messen */
			start = current_time_millis();
			
			/*
			 * Beginn der Aenderungen
			 */ 

			// Anzahl der Bild-Unterteilungen in einzelne Bl�cke
			unsigned int num_blocks = 16;
			
			// wiederholte Berechnung f�r jeden Block
			for (unsigned int i = 0; i < num_blocks; i++) {

				
				int x = 0;							// alle Bl�cke sind lediglich waagerecht unterteilt
				int y = i * height / num_blocks;	// jeder Block sitzt unterhalb seines Vorg�ngerblocks
				int w = width;						// alle Bl�cke erstrecken sich �ber die volle Bildbreite
				int h = height / num_blocks;		// jeder Block hat gleiche H�he
				
				printf("Block %d: (x,y) = (%d,%d), (w,h) = (%d,%d)\n", i, x, y, w, h);

				/* Bildberechnung durchf�hren */
				calc_mandelbrot(data + i*w*h, width, height, x, y, w, h);

			}

			/*
			 * Abschluss der Aenderungen
			 */ 

			/* berechnete Bilddaten in die Ausgabedatei schreiben */
			fwrite(data, sizeof(pixel_data_t), width*height, file);

			/* Datei schliessen */
			fclose(file);

			/* Endzeit messen und Differenz ausgeben */
			end = current_time_millis();
			printf("%.2f Sekunden\n", (double)(end-start) / 1000);

			/* positiven R�ckgabewert festlegen */
			return_code = EXIT_SUCCESS;
		} else  {
			printf("Fehler beim Erstellen der Datei: %s\n", strerror(errno));
		}
		
		/* Puffer f�r Bilddaten freigeben */
		free(data);
		
	} else {
		printf("Nicht genug Arbeitsspeicher verf�gbar.\n");
	}

	return return_code;
}
