#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include "buffer.h"
#include "util.h"


/* TODO globale Variablen hier einfügen */
FILE* file;


/* Thread Funktionalität hier ergänzen */

void* reader_thread(/*void* value*/)
{
	return NULL;
}

void* analyzer_thread(/*void* value*/)
{
	return NULL;
}

void* printer_thread(/*void* value*/)
{
	return NULL;
}

 /***************
  * BEGINN MAIN *
  ***************/

int main(int argc, char* argv[])
{
	int thread_num;
	/* TODO Benötigte lokale Variablen ergänzen */

	/* Prüfe, ob Programm mit Parametern aufgerufen wurde */
	if(argc < 3)
	{
		printf("Use %s <filename> <number_of_threads> [-stat]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if((thread_num = atoi(argv[2])) <= 0)
	{
		printf("Fehler! Threadanzahl muss eine positive Zahl größer 0 sein!\n");
		exit(EXIT_FAILURE);
	}
	/* Prüfe, ob Textdatei existiert, wenn ja, öffnen*/
	if((file = fopen(argv[1], "rb")) == NULL)
	{
		printf("Fehler beim Öffnen der Datei: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	/* TODO Initialisierung */

	/* Startzeit bestimmen */
	unsigned long start_time = current_time_millis();

	/* TODO  Threads starten */

	/* TODO auf Threads warten */

	/* Zeit messen */
	unsigned long elapsed_time = current_time_millis() - start_time;
    printf("Ausführungsdauer: %lu Millisekunden\n", elapsed_time);
    if(argc >= 4 && strcmp(argv[3], "-stat") == 0) {
		fprintf(stderr, "%s,%s,%lu\n", argv[1], argv[2], elapsed_time);
	}


	/* TODO Aufräumen*/

	fclose(file);
	return EXIT_SUCCESS;
}
