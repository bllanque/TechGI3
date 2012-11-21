/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */


#include <stdio.h>
#include <stdlib.h>
#include "vorgabe.h"
#include "FIFO.h"
#include "RR.h"
#include "RR_MLF.h"
#include "SJN.h"
#include "sem_tests.h"

#define FIFO   0
#define SJN    1
#define RR1    2
#define RR3    3
#define RR_MLF 4

/**********
 *  INIT  *
 **********/

void init_sim() {
	int i, j, k;

	/* Laenge fuer simtask-Array bestimmen */
	numtasks = MINTASKS + ( rand() % ( MAXTASKS - MINTASKS ) );

	/* Stats initialisieren */
	for ( i = 0;i < STRATS;i++ ) {
		for ( j = 0;j < numtasks;j++ ) {
			for ( k = 0;k < 5;k++ ) {
				stats[i][j][k] = 0;
			}
		}
		not_term[i] = numtasks;
	}

	/* Tasks definieren */
	for ( i = 0;i < numtasks;i++ ) {
		int start = ( rand() % ( MAXTASKS * ( MAXLENGTH - 1 ) ) ) >> 1;
		int length = MINLENGTH + ( rand() % ( MAXLENGTH - MINLENGTH ) );
		for ( j = 0;j < STRATS;j++ ) {
			tasks[j][i].start = start;
			tasks[j][i].t.id = i;
			tasks[j][i].t.length = length;
			stats[j][i][0] = start;
			stats[j][i][1] = length;
		}
	}

	/* Strategien zuordnen */
	strategies[FIFO].init = init_FIFO;
	strategies[FIFO].arrive = arrive_FIFO;
	strategies[FIFO].tick = tick_FIFO;
	strategies[FIFO].finish = finish_FIFO;
	strategies[FIFO].sem_test = test_FIFO;

	strategies[SJN].init = init_SJN;
	strategies[SJN].arrive = arrive_SJN;
	strategies[SJN].tick = tick_SJN;
	strategies[SJN].finish = finish_SJN;
	strategies[SJN].sem_test = test_SJN;

	strategies[RR1].init = init_RR_1;
	strategies[RR1].arrive = arrive_RR_1;
	strategies[RR1].tick = tick_RR_1;
	strategies[RR1].finish = finish_RR_1;
	strategies[RR1].sem_test = test_RR_1;

	strategies[RR3].init = init_RR_3;
	strategies[RR3].arrive = arrive_RR_3;
	strategies[RR3].tick = tick_RR_3;
	strategies[RR3].finish = finish_RR_3;
	strategies[RR3].sem_test = test_RR_3;

	strategies[RR_MLF].init = init_RR_MLF;
	strategies[RR_MLF].arrive = arrive_RR_MLF;
	strategies[RR_MLF].tick = tick_RR_MLF;
	strategies[RR_MLF].finish = finish_RR_MLF;
	strategies[RR_MLF].sem_test = test_RR_MLF;

	/* Gesamtstatistik initialisieren */

	for ( i = 0;i < STRATS;i++ )
		for ( j = 0;j < 4;j++ )
			final_stats[i][j] = 0;

	return;
}


/**********
 *  TEST  *
 **********/

int running;

void switch_task( int new_task ) {
	running = new_task;
}

void test( char name[], int test_strat ) {
	int i, j;
	int step = 0;
	running = IDLE;

	// test, ob Scheduler implementiert
	if ( !( implemented[test_strat] = strategies[test_strat].init() ) ) {
		printf( "semantic test: %s seems to be not implemented - check return value of init_%s()\n", name, name );
		return;
	}

	printf( "[%s]: running semantic test... \n", name );

	if ( strategies[test_strat].sem_test( &running ) ) {
		printf( "passed... \n" );
	}
	printf( "\n" );

	// Scheduler zurücksetzen und Zufallstest laufen lassen
	running = IDLE;
	strategies[test_strat].init();

	int finished = 0;

	while ( !finished ) {
		if ( not_term[test_strat] == 0 ) finished = 1;
		if ( step > MAXTASKS*MAXLENGTH ) {
			printf( "ERROR!!! All tasks should have been finished now (Step %d)!!!\n", step );
			implemented[test_strat] = 0;
			return;
		}

		/* ARRIVE */
		for ( i = 0;i < numtasks;i++ ) {
			task actual = tasks[test_strat][i].t;
			if ( tasks[test_strat][i].start == step ) {
				// simuliere geschätze Laufzeiten, konstanter Offset, damit die Reihenfolge trotzdem gleich bleibt
				strategies[test_strat].arrive( actual.id, test_strat == SJN ? actual.length - 2 : -1 );
			}
		}

		/* FIFO und SJN können (sollten) tickless implementiert werden */
		if(test_strat == RR1 || test_strat == RR3 || test_strat == RR_MLF) {
			strategies[test_strat].tick();
		}

		if ( running == IDLE ) {
			for ( j = 0;j < numtasks;j++ ) {
				simtask actual = tasks[test_strat][j];
				if ( actual.start < step && actual.t.id != IDLE && test_strat ) {
					printf( "ERROR in strategie %s!!! task %d could run now (Step %d)!\n",
													name, j + 1, step );

					implemented[test_strat] = 0;
					return;
				}
			}
		} else {
			if ( tasks[test_strat][running].t.length == 0 ) {
				printf( "ERROR in strategie %s!!! Tried to run a task (%d), that has already finished!\n",
												name, running );

				implemented[test_strat] = 0;
				return;
			}

			/* Task einen Zeitschritt arbeiten lassen */
			tasks[test_strat][running].t.length--;
			/* Statistik (gearbeitet) aktualisieren */
			stats[test_strat][running][2]++;
			/* Statistik (gewartet) aktualisieren */
			for ( j = 0;j < numtasks;j++ ) {
				if (( j != running ) )
					if ( tasks[test_strat][j].start <= step )
						if ( tasks[test_strat][j].t.id != IDLE ) {
							stats[test_strat][j][3]++;
						}
			}


			/* Task beendet? */
			if ( tasks[test_strat][running].t.length == 0 ) {
				/* Statistik (ende) aktualisieren*/
				stats[test_strat][running][4] = step;
				/* "ausklinken" */

				int endedTask = tasks[test_strat][running].t.id;
				tasks[test_strat][running].t.id = IDLE;

				not_term[test_strat]--;
				/* stimmt Taskanzahl? */
				if ( not_term[test_strat] < 0 ) {
					printf( "ERROR in strategie %s!!! ", name );
					printf( "More tasks terminated than started!\n" );
					implemented[test_strat] = 0;
					return;
				}
				/* Rechenzeit == Laenge? */
				if ( stats[test_strat][running][2] != stats[test_strat][running][1] ) {
					printf( "ERROR in strategie %s!!! ", name );
					printf( "Computing time (%d) and length (%d)\nof task ",
													stats[test_strat][running][2], stats[test_strat][running][1] );
					printf( "%d don't match!\n", running );
					implemented[test_strat] = 0;
					return;
				}

				/* Start + gerechnet + gewartet == jetzt ? */
				if ( tasks[test_strat][running].start
									+ stats[test_strat][running][2]
									+ stats[test_strat][running][3]
									!= step + 1 ) {
					printf( "ERROR in strategie %s!!!\n", name );
					printf( "starting time(%d)\n", stats[test_strat][running][0] );
					printf( "+ waiting time(%d)\n", stats[test_strat][running][3] );
					printf( "+ computing time(%d)\n", stats[test_strat][running][2] );
					printf( "of task %d ", running );
					printf( "doesn't match actual time-step %d!\n", step + 1 );
					implemented[test_strat] = 0;
					return;
				}

				strategies[test_strat].finish( endedTask );
			}

		}
		step++;
	}
}

/*************
 * STATISTIC *
 *************/

void get_statistics( char *name, int test_strat ) {
	int j;
	for ( j = 0;j < numtasks;j++ ) {
		final_stats[test_strat][0] += ( float )stats[test_strat][j][3];
		final_stats[test_strat][1] += ( float )stats[test_strat][j][2];
	}

	final_stats[test_strat][2] = ( float )( final_stats[test_strat][0] ) / ( float )( numtasks );
	final_stats[test_strat][3] = ( float )( final_stats[test_strat][0] ) / ( float )( final_stats[test_strat][1] );


	printf( "Statistic for %s:\n", name );
	printf( "%d tasks\n", numtasks );
	printf( "Summed Waiting Time: %f\n", final_stats[test_strat][0] );
	printf( "Summed computing time: %f\n", final_stats[test_strat][1] );
	printf( "Average Waiting Time: %f\n", final_stats[test_strat][2] );
	printf( "Summed Waiting Time divided by summed computing time: %f\n", final_stats[test_strat][3] );
	printf( "\n" );
}
