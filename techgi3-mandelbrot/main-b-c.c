#include "bitmap.h"
#include "mandelbrot.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define WIDTH  3200
#define HEIGHT 2400
#define COUNT 64

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

	/* Bestimmung geeigneter Blockgrš§e */
	int lower = COUNT, upper = COUNT;									// untere und obere Schranke der Blockanzahl
	int count;															// Anzahl Blšcke (sollte Teiler von HEIGHT sein!)

	while (HEIGHT % lower != 0) lower--;								// obere Schranke (nŠchstgrš§erer Teiler)
	while (HEIGHT % upper != 0) upper++;								// untere Schranke (nŠchstkleinerer Teiler) 

	count = ((upper - count) < (count -lower)) ? upper : lower;			// als Blockzahl wird nŠchstbester Teiler verwendet

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
			
			/* Bilddatei vorŸbergehend schlie§en */		
  			if (fclose(file) == 0) {
						
				for (int block = 0; block < count; block++) {		// Blšcke in einer Schleife berechnen
					
					if (fork() == (pid_t) 0) {						// sind wir parent oder child?

						/* blockspezifische Parameter berechnen */
						int y = block * height / count;				// jeder Block sitzt unterhalb seines Vorgaengerblocks
						int h = height / count;						// jeder Block hat gleiche Hoehe
						int rank = getpid();						// ggf. Nummer des aktuellen Threads
						
						/* wir sind Child */
						printf("Block %3d von %d berechnet von Prozess %3d: (x1,y1) = (%d,%4d), (x2,y2) = (%d,%4d)\n", block+1, count, rank, 0, y, width, (block+1) * h);
		
						/* Bildberechnung durchführen */
						calc_mandelbrot(data + block * width * h, width, height, 0, y, width, h);
	
						/* Datei wieder zum schreiben šffnen */   
						file = fopen(filename, "rb+");
						
						/* Schreibposition bestimmen */
						int ofs = BITMAP_HEADER_SIZE + block * width * h * sizeof(pixel_data_t); 
						
						/* Schreibposition suchen */
						fseek(file, ofs, SEEK_SET);
						
						/* Bitmap-Block schreiben */
						printf("Block %3d von %d berechnet von Prozess %3d: Dateioffset %d\n", block+1, count, rank, ofs);

						/* berechnete Bilddaten in die Ausgabedatei schreiben */
						fwrite(data + block * width * h, sizeof(pixel_data_t), width * h, file);

						/* Datei schliessen */
						fclose(file);

						/* Kindprozess beenden */
						exit(0);
					}
				} 
			
 			} else
				printf("Fehler bei der Freiabe der Datei: %s\n", strerror(errno));

			pid_t wpid;

				/* Beendigung aller Kindprozesse abwarten */
			while ((wpid = wait(0)) > 0) {
				printf("Prozess %3d: terminiert\n", (int) wpid);
        	}
            
			/* Endzeit messen und Differenz ausgeben */
			end = current_time_millis();
			printf("%.2f Sekunden\n", (double)(end-start) / 1000);

			/* positiven Rückgabewert festlegen */
			return_code = EXIT_SUCCESS;
		} else {
			printf("Fehler beim Erstellen der Datei: %s\n", strerror(errno));
		}
		
		/* Puffer für Bilddaten freigeben */
		free(data);
		
	} else {
		printf("Nicht genug Arbeitsspeicher verfügbar.\n");
	}

	return return_code;
}
