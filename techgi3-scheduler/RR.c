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
	tick = 0;
	step = 1;

	if (queue) free(queue);
	
	queue = (LIST*) malloc(sizeof(LIST));
	queue->first = NULL;
	queue->last = NULL;
	
	return 1;
}

void arrive_RR_1( int id , int length ) {
	appendTask(queue, id, length);
	
	switch_task(queue->first->task->id);
}

void tick_RR_1() {
	if ((tick = tick++ % step) == 0)
		appendNode(queue, removeFirst(queue));

	switch_task((queue->first) ? queue->first->task->id : IDLE);
}

void finish_RR_1( int id ) {
	removeTask(queue, id);
	
	switch_task((queue->first) ? queue->first->task->id : IDLE);
}

/**********************************************************
 ********     ROUND ROBIN mit Zeitscheibe T=3s     ********
 **********************************************************/

int init_RR_3() {
	init_RR_1();
	step = 3;

	return 1;
}

void arrive_RR_3( int id , int length ) {
	arrive_RR_1(id, length);
}

void tick_RR_3() {
	tick_RR_1();
}

void finish_RR_3( int id ) {
	finish_RR_1(id);
}
