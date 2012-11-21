/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#include "system.h"

#ifndef AUFG7_SJN
#define AUFG7_SJN

/* zur Initialisierung eventuell noetiger Datenstrukturen */
int init_SJN();
/* informiert den Scheduler ueber neue Tasks */
void arrive_SJN( int, int );
/* wird vom System zu beginn jeder Zeiteinheit aufgerufen */
void tick_SJN();
/* informiert den Scheduler über die Beendigung eines Tasks */
void finish_SJN( int );

#endif

