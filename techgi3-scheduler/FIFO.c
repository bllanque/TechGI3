#include <stdlib.h>
#include <stdio.h>

#include "FIFO.h"
#include "tasklist.h"
#include "system.h"

LIST* queue;

int init_FIFO() {
	if (queue) free(queue);					// remove old queue upon (re-)start

	queue = (LIST*) malloc(sizeof(LIST));	// allocate space for the queue
	queue->first = NULL;					// mark the list...
	queue->last = NULL;						// ...as empty

	return 1;
}

void arrive_FIFO( int id , int length ) {
	appendTask(queue, id, length);			// a fifo takes input at it's rear end ;)
	
	switch_task(queue->first->task->id);	// after appending a task, the queue is non-empty
}

void tick_FIFO() {
	/* UNUSED */
}

void finish_FIFO( int id ) {
	removeTask(queue, id);					// remove task from queue
											// the list might be empty now -> IDLE
	switch_task((queue->first) ? queue->first->task->id : IDLE);
}
