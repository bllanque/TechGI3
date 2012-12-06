#ifndef UTIL_H
#define UTIL_H

#include "buffer.h"


#define CHUNKSIZE 1000
#define RESULTSIZE 150
#define MINLEN 10
#define BUFFER_SIZE 10


/**
 * SUCHFUNKTION:
 *
 * Sucht in dem übergebenen Speicherbereich "chunk" mit der angegebenen Länge
 * "size" nach Wiederholungen. Für jede gefundene Wiederholung wird ein
 * Speicherblock allokiert, der sich wiederholende String dort hineinkopiert
 * und der neue Block in den angegebenen Ringpuffer eingefügt.
 */
void search_and_insert(char* chunk, unsigned int size, ringbuffer_t* buf);


/**
 * Gibt die Anzahl der Millisekunden seit Epochenbeginn zurück.
 */
unsigned long current_time_millis();


#endif
