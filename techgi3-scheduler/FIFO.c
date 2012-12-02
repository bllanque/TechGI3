#include <stdlib.h>
#include <stdio.h>

#include "FIFO.h"
#include "tasklist.h"
#include "system.h"

LIST* queue;

int init_FIFO() {
	if (queue) free(queue);

	queue = (LIST*) malloc(sizeof(LIST));
	queue->first = NULL;
	queue->last = NULL;

	return 1;
}

void arrive_FIFO( int id , int length ) {
	appendTask(queue, id, length);
	
	switch_task(queue->first->task->id);
}

void tick_FIFO() {
	/* UNUSED */
}

void finish_FIFO( int id ) {
	removeTask(queue, id);
	
	switch_task((queue->first) ? queue->first->task->id : IDLE);
}
