#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "RR_MLF.h"
#include "tasklist.h"
#include "system.h"

#define DEBUG_
#define LEVELS 4

LIST* level[LEVELS];
int   progress[LEVELS];

int init_RR_MLF() {

	for (int i=0; i < LEVELS; i++) {
		if (level[i]) free(level[i]);
	
		level[i] = (LIST*) malloc(sizeof(LIST));
		level[i]->first = NULL;
		level[i]->last = NULL;
		
		progress[i] = 0;
	}

	return 1;
}

void arrive_RR_MLF( int id, int length ) {	

	#ifdef DEBUG 
	printf("debug: running task %d after arrival (on level 0)\n", id);
	#endif

	appendTask(level[0], id, length);
	
	switch_task(level[0]->first->task->id);
}

void tick_RR_MLF() {

	for (int i=0; i < LEVELS; i++) {
		progress[i] = progress[i] % (int) pow(2, i+2);
		
		#ifdef DEBUG 
		printf("debug: level %d is at progress %d of %d\n", i, progress[i], (int) pow(2, i+2)); 
		#endif
			
		if (level[i]->first) {
			if (progress[i] == 0 && i < LEVELS-1) {
			
				#ifdef DEBUG
				printf("debug: demoting task %d from level %d to %d\n", level[i]->first->task->id, i, i+1);
				#endif

				appendNode(level[i+1], removeFirst(level[i]));
				break;
			}
		}
		else
			progress[i] = 0;
			
	}

	for (int i=0; i < LEVELS; i++) {
		if (level[i]->first) {

			#ifdef DEBUG
			printf("debug: running task %d from level %d \n", level[i]->first->task->id, i);
			#endif

			progress[i]++;
			switch_task(level[i]->first->task->id);
			return;
		}
	}

	switch_task(IDLE);
}

void finish_RR_MLF( int id ) {

	for (int i=0; i < LEVELS; i++)
		if (level[i]->first) {

			#ifdef DEBUG
			printf("debug: removing task %d from level %d \n", id, i);
			#endif

			removeTask(level[i], id);
			progress[i] = 0;
			break;
		}
	
	for (int i=0; i < LEVELS; i++)
		if (level[i]->first) {
		
			#ifdef DEBUG
			printf("debug: switching to task %d from level %d \n", level[i]->first->task->id, i);
			#endif

			switch_task(level[i]->first->task->id);
			return;
		}

	switch_task(IDLE);
}
