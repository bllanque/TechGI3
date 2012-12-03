#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "RR_MLF.h"
#include "tasklist.h"
#include "system.h"

#define DEBUG
#define LEVELS 4

LIST* queue[LEVELS];
int   tick[LEVELS];

int init_RR_MLF() {

	for (int i=0; i < LEVELS; i++) {
		if (queue[i]) free(queue[i]);
	
		queue[i] = (LIST*) malloc(sizeof(LIST));
		queue[i]->first = NULL;
		queue[i]->last = NULL;
		
		tick[i] = 0;
	}

	return 1;
}

void arrive_RR_MLF( int id, int length ) {	

	#ifdef DEBUG 
	printf("debug: running task %d after arrival (on queue 0)\n", id);
	#endif

	appendTask(queue[0], id, length);
	
	switch_task(queue[0]->first->task->id);
}

void tick_RR_MLF() {

	for (int i=0; i < LEVELS; i++) {
		tick[i] = tick[i] % (int) pow(2, i+2);
		
		#ifdef DEBUG 
		printf("debug: queue %d is at tick %d of %d\n", i, tick[i], (int) pow(2, i+2)); 
		#endif
			
		if (queue[i]->first) {
			if (tick[i] == 0 && i < LEVELS-1) {
			
				#ifdef DEBUG
				printf("debug: demoting task %d from queue %d to %d\n", queue[i]->first->task->id, i, i+1);
				#endif

				appendNode(queue[i+1], removeFirst(queue[i]));
				break;
			}
		}
		else
			tick[i] = 0;
			
	}

	for (int i=0; i < LEVELS; i++) {
		if (queue[i]->first) {

			#ifdef DEBUG
			printf("debug: running task %d from queue %d \n", queue[i]->first->task->id, i);
			#endif

			tick[i]++;
			switch_task(queue[i]->first->task->id);
			return;
		}
	}

	switch_task(IDLE);
}

void finish_RR_MLF( int id ) {

	for (int i=0; i < LEVELS; i++)
		if (queue[i]->first) {

			#ifdef DEBUG
			printf("debug: removing task %d from queue %d \n", id, i);
			#endif

			removeTask(queue[i], id);
			tick[i] = 0;
			break;
		}
	
	for (int i=0; i < LEVELS; i++)
		if (queue[i]->first) {
		
			#ifdef DEBUG
			printf("debug: switching to task %d from queue %d \n", queue[i]->first->task->id, i);
			#endif

			switch_task(queue[i]->first->task->id);
			return;
		}

	switch_task(IDLE);
}
