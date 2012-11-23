#include "bitmap.h"
#include "mandelbrot.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

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
			
			/* Beginn der €nderungen */			
			int count = 60;									// Anzahl Blšcke (muss Teiler von HEIGHT sein!)
			int block;										// Index des aktuellen Blocks 
			int rank;										// ggf. Nummer des aktuellen Threads
			
			#ifdef _OPENMP
			#pragma omp parallel private(rank, block)		// Laufvariable und Threadnummer eindeutig je Thread
			#endif
			{
				#ifdef _OPENMP
            	rank = omp_get_thread_num();				// via OpenMP Threadnummer ermitteln				
				#pragma omp for
				#endif

				for (block = 0; block < count; block++) 	// Blšcke in einer Schleife berechnen
				{
					int y = block * height / count;			// jeder Block sitzt unterhalb seines Vorgaengerblocks
					int h = height / count;					// jeder Block hat gleiche Hoehe
					
					printf("Block %3d von %d berechnet von Thread %3d: (x1,y1) = (%d,%4d), (x2,y2) = (%d,%4d)\n", block+1, count, rank, 0, y, width, (block+1) * h);
	
					/* Bildberechnung durchführen */
					calc_mandelbrot(data + block * width * h, width, height, 0, y, width, h);
				}
				
			}
            /* Abschluss der €nderungen */
            
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
