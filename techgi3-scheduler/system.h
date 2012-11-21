/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#ifndef AUFG7_SYSTEM
#define AUFG7_SYSTEM

/* maximale Anzahl von Tasks, die während des Tests laufen werden */
#define MAXTASKS 512

/* spezielle Task-ID, falls kein Task mehr laufbereit ist oder alle abgearbeitet wurden */
#define IDLE -1

/*
 Der Aufruf dieser Funktion veranlasst im System einen Task-Wechsel zum übergebenen Task.
*/
void switch_task( int id );

#endif
