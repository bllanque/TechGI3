/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#include "sem_tests.h"

#include <stdio.h>
#include <stdlib.h>
#include "FIFO.h"
#include "RR.h"
#include "RR_MLF.h"
#include "SJN.h"

typedef struct task_t {
	int id;
	int length;
} task;

#define MAXTESTTASKS 5

// stellt sicher, dass der IDLE prozess läuft
int test_idle( int* running ) {
	if (*running != IDLE) {
		printf( "ERROR!!! task %d is running instead of IDLE task!!!\n", *running );
		return 0;
	}

	return 1;
}

// einfacher Test: überprüfe, ob Tasks wirklich in Fifo Reihenfolge abgearbeitet werden.
int test_FIFO( int* running ) {
	task testTask[MAXTESTTASKS] = {{0, 5}, {1, 4}, {2, 3}, {3, 2}, {4, 1}};

	int k = 0;

	int i;
	for ( i = 0; i < MAXTESTTASKS; i++ ) {
		int j;
		for ( j = 0; j < testTask[i].length; j++ ) {
			if ( k < MAXTESTTASKS ) {
				arrive_FIFO( testTask[k].id, -1 /* testTask[k].length */ );
				k++;
			}

			if ( *running < 0 || *running >= MAXTESTTASKS ) {
				printf( "ERROR!!! Scheduler switched to invalid task id (%d)!!!\n", *running );
				return 0;
			}

			// printf( "Running Task: %d\n", *running );
			// printf( "Task remaining length: %d\n", testTask[*running].length  - j - 1 );

			if ( *running != i ) {
				// j == 0 -> letzter Task wurde beendet, aber dann zum falschen gewechselt
				if ( j == 0 ) {
					if(i < *running)
						printf( "ERROR!!! Scheduler switched to task %d, but task %d has arrived earlier!\n", *running, i );
					else
						printf( "ERROR!!! Task %d is still running but should have finished by now!\n", *running );
				} else
					// j != 0 -> der Task i war noch nicht fertig, es wurde zu früh gewechselt
					printf( "ERROR!!! Scheduler switched to task %d, but task %d hasn't finished yet!\n", *running, i );

				return 0;
			}
		}

		finish_FIFO( testTask[i].id );
	}

	return test_idle( running );
}

// Sortierung der Tasks testen
int test_SJN( int* running ) {
	task testTask[MAXTESTTASKS] = {{0, 9}, {1, 8}, {2, 7}, {3, 6}, {4, 5}};
	// Task-Sequenz
	task switchSequence[MAXTESTTASKS] = {{0, 9}, {4, 5}, {3, 6}, {2, 7}, {1, 8}};

	// Tasks hinzufügen
	int i;
	for ( i = 0; i < MAXTESTTASKS; i++ ) {
		arrive_SJN( testTask[i].id, testTask[i].length - 2);
	}

	for ( int task_num = 0; task_num < MAXTESTTASKS; task_num++ ) {
		if ( *running != switchSequence[task_num].id ) {
			printf( "ERROR!!! Scheduler switched to task %d, but task %d is shorter!\n", *running, switchSequence[task_num].id );
			return 0;
		}
		finish_SJN( switchSequence[task_num].id );
	}

	return test_idle( running );
}

// einfacher Test für RR Verhalten: gleichmäßige CPU Zuteilung und alle delta-Zeiteinheiten ein anderer Task
int testRR( int delta, int* running, void ( *arrive )( int, int ), void ( *tick )(), void ( *finish )( int ) ) {
	task testTask[MAXTESTTASKS] = {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}};

	int i;
	for ( i = 0; i < MAXTESTTASKS; i++ ) {
		arrive( testTask[i].id, -1 /* testTask[i].length */ );
	}

	int lastTask = IDLE;
 	int ete = 1;
 
	for ( i = 0; i < 30 / delta; i++ ) {
		for ( int k = 0; k < delta; k++ ) {
//			printf("\n\ni=%i, k=%i\n\n",i,k);
			tick();

			if ( lastTask == *running ) {
				printf( "ERROR!!! Scheduler ran the same Task (%d) twice!\n", *running );
				return 0;
			}

			if ( *running < 0 || *running >= MAXTESTTASKS ) {
				printf( "ERROR!!! Scheduler switched to invalid task id (%d)!\n", *running );
				return 0;
			}

//			printf( "Running Task: %d\n", *running );
			testTask[*running].length--;
//			printf( "Task remaining length: %d\n", testTask[*running].length );

			int j;
			for ( j = 0; j < MAXTESTTASKS; j++ ) {
				if ( abs( testTask[*running].length - testTask[j].length ) > delta ) {
					printf( "ERROR!!! Task %d had more cpu time than task %d!\n", *running, j );
					return 0;
				}
			}
			
//			printf("Das war die %i. Zeiteinheit\n\n",ete++);

			if ( testTask[*running].length == 0 ) {
				break;
			}
		}

		lastTask = *running;
		if ( testTask[*running].length == 0 ) {
		    finish( testTask[*running].id );
		}
	}

	// letzter tick zum Umschalten auf idle
	tick();

	return test_idle( running );
}

int test_RR_1( int* running ) {
	return testRR( 1, running, arrive_RR_1, tick_RR_1, finish_RR_1 );
}

int test_RR_3( int* running ) {
	return testRR( 3, running, arrive_RR_3, tick_RR_3, finish_RR_3 );
}

int test_RR_MLF( /* int* running */ ) {
	// freiwillige Aufgabe
	return 1;
}
