/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#include "system.h"

#ifndef AUFG7_RR
#define AUFG7_RR


/* zur Initialisierung eventuell noetiger Datenstrukturen */
int init_RR_1();
int init_RR_3();
/* informiert den Scheduler ueber neue Tasks */
void arrive_RR_1( int, int );
void arrive_RR_3( int, int );
/* wird vom System zu beginn jeder Zeiteinheit aufgerufen */
void tick_RR_1();
void tick_RR_3();
/* informiert den Scheduler über die Beendigung eines Tasks */
void finish_RR_1( int );
void finish_RR_3( int );

#endif
