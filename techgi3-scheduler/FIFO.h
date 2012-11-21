/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#include "system.h"

#ifndef AUFG7_FIFO
#define AUFG7_FIFO


/* zur Initialisierung eventuell noetiger Datenstrukturen */
int init_FIFO();
/* informiert den Scheduler ueber neue Tasks */
void arrive_FIFO( int, int );
/* wird vom System zu beginn jeder Zeiteinheit aufgerufen */
void tick_FIFO();
/* informiert den Scheduler über die Beendigung eines Tasks */
void finish_FIFO( int );

#endif
