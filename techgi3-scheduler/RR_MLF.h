/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#include "system.h"

#ifndef AUFG7_RR_MLF
#define AUFG7_RR_MLF

/* zur Initialisierung eventuell noetiger Datenstrukturen */
int init_RR_MLF();
/* informiert den Scheduler ueber neue Tasks */
void arrive_RR_MLF( int, int );
/* wird vom System zu beginn jeder Zeiteinheit aufgerufen */
void tick_RR_MLF();
/* informiert den Scheduler über die Beendigung eines Tasks */
void finish_RR_MLF( int );

#endif
