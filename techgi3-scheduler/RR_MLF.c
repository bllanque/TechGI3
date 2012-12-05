#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "RR_MLF.h"
#include "tasklist.h"
#include "system.h"

#define DEBUG_													// switch for proof of work
#define LEVELS 4												// set between 1 and 9

LIST* level[LEVELS];											// priority level queues
int   progress[LEVELS];											// level runtime counters

int init_RR_MLF() {

	for (int i=0; i < LEVELS; i++) {							// consider all priority levels
		if (level[i]) free(level[i]);							// remove old queues upon (re-)start
	
		level[i] = (LIST*) malloc(sizeof(LIST));				// allocate space for a queues
		level[i]->first = NULL;									// mark the list...
		level[i]->last = NULL;									// ...as empty
		
		progress[i] = 0;										// (re-)start all queues from the beginning
	}

	return 1;
}

void arrive_RR_MLF( int id, int length ) {	

	#ifdef DEBUG 
	printf("debug: running task %d after arrival (on level 0)\n", id);
	#endif

	appendTask(level[0], id, length);							// RR uses a fifo to queue
	
	switch_task(level[0]->first->task->id);						// select first task in first non-empty queue
}

void tick_RR_MLF() {

	for (int i=0; i < LEVELS; i++) {							// consider all priority levels
		progress[i] = progress[i] % (int) pow(2, i+2);			// progressively reduce level priority 
		
		#ifdef DEBUG 
		printf("debug: level %d is at progress %d of %d\n", i, progress[i], (int) pow(2, i+2)); 
		#endif
			
		if (level[i]->first) {									// select first task in first non-empty queue
			if (progress[i] == 0 && i < LEVELS-1) {				// once a task used up it's prioritized time slice
			
				#ifdef DEBUG
				printf("debug: demoting task %d from level %d to %d\n", level[i]->first->task->id, i, i+1);
				#endif

				appendNode(level[i+1], removeFirst(level[i]));	// reduce that task's priority by
				break;											// moving to the next level 
			}
		}
		else
			progress[i] = 0;									// keep all non-active levels from working
			
	}

	for (int i=0; i < LEVELS; i++) {							// consider all priority levels *again*
		if (level[i]->first) {									// select first task in first *now* non-empty queue

			#ifdef DEBUG
			printf("debug: running task %d from level %d \n", level[i]->first->task->id, i);
			#endif

			progress[i]++;										// remember which level received attention
			switch_task(level[i]->first->task->id);				// let this task do it's work
			return;												// prevent accidental task switching
		}
	}

	switch_task(IDLE);											// if all level queues are empty -> IDLE
}

void finish_RR_MLF( int id ) {

	for (int i=0; i < LEVELS; i++)								// consider all priority levels
		if (level[i]->first) {									// select first task in first non-empty queue

			#ifdef DEBUG
			printf("debug: removing task %d from level %d \n", id, i);
			#endif

			removeTask(level[i], id);							// remove task from queue
			progress[i] = 0;									// next task deserves it's full time slice
			break;
		}
	
	for (int i=0; i < LEVELS; i++)								// consider all priority levels *again*
		if (level[i]->first) {									// select first task in first *now* non-empty queue
		
			#ifdef DEBUG
			printf("debug: switching to task %d from level %d \n", level[i]->first->task->id, i);
			#endif

			switch_task(level[i]->first->task->id);				// let this task do it's work
			return;												// prevent accidental task switching
		}

	switch_task(IDLE);											// if all level queues are empty -> IDLE
}
