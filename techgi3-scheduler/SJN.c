#include <stdlib.h>
#include <stdio.h>

#include "SJN.h"
#include "tasklist.h"
#include "system.h"

LIST* queue;

int init_SJN() {
	if (queue) free(queue);					// remove old queue upon (re-)start
	
	queue = (LIST*) malloc(sizeof(LIST));	// allocate space for a queue
	queue->first = NULL;					// mark the list...
	queue->last = NULL;						// ...as empty
	
	return 1;
}

void arrive_SJN( int id, int length ) {
	insertTask(queue, id, length);			// a sjn queue sorts it's input by length (asc)
	
	switch_task(queue->first->task->id);	// after inserting a task, the queue is non-empty
}

void tick_SJN() {
	/* UNUSED */
}

void finish_SJN( int id ) {
	removeTask(queue, id);					// remove task from queue
											// the list might be empty now -> IDLE
	switch_task((queue->first) ? queue->first->task->id : IDLE);
}
