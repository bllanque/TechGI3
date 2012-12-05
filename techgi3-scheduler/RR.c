#include <stdlib.h>
#include <stdio.h>

#include "RR.h"
#include "tasklist.h"
#include "system.h"

LIST* queue;
int tick = 0;
int step;

/**********************************************************
 ********     ROUND ROBIN mit Zeitscheibe T=1s     ********
 **********************************************************/

int init_RR_1() {
	tick = 0;										// make sure we start at the beginning
	step = 1;										// set RR_1 with T=1

	if (queue) free(queue);							// remove old queue upon (re-)start
	
	queue = (LIST*) malloc(sizeof(LIST));			// allocate space for a queue
	queue->first = NULL;							// mark the list...
	queue->last = NULL;								// ...as empty
	
	return 1;
}

void arrive_RR_1( int id , int length ) {
	appendTask(queue, id, length);					// RR uses a fifo to queue

	switch_task(queue->first->task->id);			// after inserting a task, the queue is non-empty
}

void tick_RR_1() {
	if ((tick = tick % step) == 0 && queue->first)	// once the tick count flows over the step size
		appendNode(queue, removeFirst(queue));		// rotate the leading element to the trailing end
													// the list might be empty anyway -> IDLE
	switch_task((queue->first) ? queue->first->task->id : IDLE);
		
	tick++;											// remember how many ticks have passed
}

void finish_RR_1( int id ) {
	removeTask(queue, id);							// remove task from queue
													// the list might be empty now -> IDLE
	switch_task((queue->first) ? queue->first->task->id : IDLE);
}

/**********************************************************
 ********     ROUND ROBIN mit Zeitscheibe T=3s     ********
 **********************************************************/

int init_RR_3() {
	init_RR_1();									// handle like RR_1
	step = 3;										// except for the step size T=3

	return 1;
}

void arrive_RR_3( int id , int length ) {
	arrive_RR_1(id, length);						// handle like RR_1
}

void tick_RR_3() {
	tick_RR_1();									// handle like RR_1
}

void finish_RR_3( int id ) {
	finish_RR_1(id);								// handle like RR_1
}
