#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>

/** Fassungsvermögen des Ringpuffers */
#define RINGBUFFER_SIZE 20

/**
 * Repräsentiert ein synchronisiertes Ringpuffer-Objekt mit fester Länge
 * und enthält alle dazu notwendigen Strukturen.
 */
typedef struct
{
    /* TODO Synchronisationsvariablen hinzufügen */

    /* TODO nötige Datenstrukturen ergänzen*/

} ringbuffer_t;

/**
 * Initialisiert die übergebene Ringpufferstruktur und alle eventuell darin
 * enthaltenen Strukturen. Verlief die Initialisierung fehlerfrei soll 0
 * zurückgegeben werden, andernfalls ein Wert ungleich 0.
 */
int init_buffer(ringbuffer_t* buf);

/**
 * Fügt den übergebenen Zeiger auf eine Zeichenkette str in den angegebenen
 * Ringpuffer buf ein. Bei einem vollen Puffer soll der Funktionsaufruf
 * blockieren, bis wieder Platz verfügbar ist.
 */ 
void deposit(ringbuffer_t* buf, char* str);

/**
 * Entnimmt das vorderste Element aus dem angegebenen Ringpuffer buf und gibt
 * dieses zurück. Ist der Puffer leer soll der Funktionsaufruf blockieren, bis
 * wieder ein Element verfügbar ist.
 */ 
char* fetch(ringbuffer_t* buf);

/**
 * Zerstört den übergebenen Ringpuffer buf und gibt alle darin enthaltenen
 * Strukturen frei.
 */ 
void destroy_buffer(ringbuffer_t* buf);

#endif
