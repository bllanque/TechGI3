#include <stdlib.h>
#include <stdio.h>

#include "FIFO.h"
#include "tasklist.h"
#include "system.h"

LIST* fifo;

int init_FIFO() {
	printf("debug: init_FIFO: entering\n");

	fifo = (LIST*) malloc(sizeof(LIST));
	fifo->first = NULL;
	fifo->last = NULL;

	printf("debug: init_FIFO: leaving\n");
	return 1;
}

void arrive_FIFO( int id , int length ) {
	printf("debug: arrive_FIFO: entering\n");
	appendTaskByID(fifo, id, length);
	
	switch_task(fifo->first->task->id);
	printf("debug: arrive_FIFO: leaving\n");
}

void tick_FIFO() {
	/* UNUSED */
}

void finish_FIFO( int id ) {
	printf("debug: finish_FIFO: entering\n");
	removeTaskById(fifo, id);
	
	if (fifo->first)
		switch_task(fifo->first->task->id);
	else
		switch_task(IDLE);
	
	printf("debug: finish_FIFO: leaving\n");
}
