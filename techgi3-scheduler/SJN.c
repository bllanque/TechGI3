#include <stdlib.h>
#include <stdio.h>

#include "SJN.h"
#include "tasklist.h"
#include "system.h"

LIST* list;

int init_SJN() {
	if (list) free(list);
	
	list = (LIST*) malloc(sizeof(LIST));
	list->first = NULL;
	list->last = NULL;
	
	return 1;
}

void arrive_SJN( int id, int length ) {
	insertTaskSJN(list, id, length);
	
	switch_task(list->first->task->id);
}

void tick_SJN() {
	/* UNUSED */
}

void finish_SJN( int id ) {
	removeTask(list, id);
	
	if (list->first)
		switch_task(list->first->task->id);
	else 
		switch_task(IDLE);
}
