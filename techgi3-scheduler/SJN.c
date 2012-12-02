#include <stdlib.h>
#include <stdio.h>

#include "SJN.h"
#include "tasklist.h"
#include "system.h"

LIST* queue;

int init_SJN() {
	if (queue) free(queue);
	
	queue = (LIST*) malloc(sizeof(LIST));
	queue->first = NULL;
	queue->last = NULL;
	
	return 1;
}

void arrive_SJN( int id, int length ) {
	insertTask(queue, id, length);
	
	switch_task(queue->first->task->id);
}

void tick_SJN() {
	/* UNUSED */
}

void finish_SJN( int id ) {
	removeTask(queue, id);
	
	switch_task((queue->first) ? queue->first->task->id : IDLE);
}
