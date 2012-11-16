#include "bitmap.h"
#include "mandelbrot.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <omp.h>

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

	/* Größe des gesamten, zu erzeugenden Bildes festlegen */
	int width = WIDTH, height = HEIGHT;

	/* Puffer für Bilddaten allokieren */
	pixel_data_t *data = calloc(width*height, sizeof(pixel_data_t));
	if (data) {

		/* Neue Ausgabedatei erstellen und zum Schreiben öffnen */
		FILE *file = fopen(filename, "wb");
		if (file) {

			/* BMP-Header schreiben */
			write_bitmap_header(file, width, height);

			/* Startzeit messen */
			start = current_time_millis();
			
#ifdef _OPENMP
			/* mit OpenMP rechnen */
			#pragma omp parallel 
			{
                int i = omp_get_thread_num();			// Nummer des aktuellen Threads
                int count = omp_get_num_threads();		// Anzahl der insgesamt verfŸgbaren Threads
#else
			/* sequentiell rechnen */
			int count = 16;								// Anzahl sequentieller Schritte 
			for (int i = 0; i < count; i++) 			// welche als Schleife ausgefŸhrt werden
			{
#endif
				int y = i * height / count;				// jeder Block sitzt unterhalb seines Vorgaengerblocks
				int h = height / count;					// jeder Block hat gleiche Hoehe
				
				printf("Block %d: (x,y) = (%d,%d), (w,h) = (%d,%d)\n", i, 0, y, width, (i+1) * h);

				/* Bildberechnung durchführen */
				calc_mandelbrot(data + i * width * h, width, height, 0, y, width, h);
			}
            
			/* berechnete Bilddaten in die Ausgabedatei schreiben */
			fwrite(data, sizeof(pixel_data_t), width*height, file);

			/* Datei schliessen */
			fclose(file);

			/* Endzeit messen und Differenz ausgeben */
			end = current_time_millis();
			printf("%.2f Sekunden\n", (double)(end-start) / 1000);

			/* positiven Rückgabewert festlegen */
			return_code = EXIT_SUCCESS;
		} else  {
			printf("Fehler beim Erstellen der Datei: %s\n", strerror(errno));
		}
		
		/* Puffer für Bilddaten freigeben */
		free(data);
		
	} else {
		printf("Nicht genug Arbeitsspeicher verfügbar.\n");
	}

	return return_code;
}
