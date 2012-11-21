/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#ifndef AUFG7_VORG
#define AUFG7_VORG

#include "system.h"

/* minimale Anzahl von Tasks, die während des Tests laufen werden */
#define MINTASKS 128
/* minimale und maximale Task-Dauer */
#define MINLENGTH 8
#define MAXLENGTH 256

/* Anzahl der Strategien */
#define STRATS 5

/* Datenstruktur zum Halten von Task-Informationen*/
typedef struct task_t {
	int id;
	int length;
}task;

/* fuer die Simulation */
typedef struct simtask_t {
	task t;
	int start;
}simtask;

typedef struct strategy_t {
	int ( *init )();
	void ( *arrive )( int, int );
	void ( *tick )();
	void ( *finish )( int );
	int ( *sem_test )( int* );
}strategy;

/* Strategien */
strategy strategies[STRATS];
int implemented[STRATS];
/* Anzahl der zu simulierenden Tasks */
int numtasks;
/* Tabellen fuer Statistik */
int not_term[STRATS];
/* start, laenge, rechenzeit, wartezeit, ende */
int stats[STRATS][MAXTASKS][5];
simtask tasks[STRATS][MAXTASKS];

/* Gesamtstatistik:
 *******************
   Gesamtwartezeit
   Gesamtrechenzeit
   durchschnittliche Wartezeit
   verhaeltnis Wartezeit zu Rechenzeit
 */
float final_stats[STRATS][4];

/* Simulation */
void init_sim();
void test( char* name, int test_strat );
void get_statistics( char *name, int test_strat );

#endif
