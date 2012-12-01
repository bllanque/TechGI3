#include <stdlib.h>
#include <stdio.h>

#include "FIFO.h"
#include "tasklist.h"
#include "system.h"

LIST* fifo;

int init_FIFO() {
	if (fifo) free(fifo);

	fifo = (LIST*) malloc(sizeof(LIST));
	fifo->first = NULL;
	fifo->last = NULL;

	return 1;
}

void arrive_FIFO( int id , int length ) {
	appendTask(fifo, id, length);
	
	switch_task(fifo->first->task->id);
}

void tick_FIFO() {
	/* UNUSED */
}

void finish_FIFO( int id ) {
	removeTask(fifo, id);
	
	if (fifo->first)
		switch_task(fifo->first->task->id);
	else 
		switch_task(IDLE);
}
