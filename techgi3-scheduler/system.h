/* *********************************************** *
 * Diese Vorgabedatei soll NICHT ge�ndert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf �nderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#ifndef AUFG7_SYSTEM
#define AUFG7_SYSTEM

/* maximale Anzahl von Tasks, die w�hrend des Tests laufen werden */
#define MAXTASKS 512

/* spezielle Task-ID, falls kein Task mehr laufbereit ist oder alle abgearbeitet wurden */
#define IDLE -1

/*
 Der Aufruf dieser Funktion veranlasst im System einen Task-Wechsel zum �bergebenen Task.
*/
void switch_task( int id );

#endif
