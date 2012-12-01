#include <stdlib.h>
#include <stdio.h>

#include "tasklist.h"
#include "system.h"

void insertTaskSJN(LIST* list, int id, int length) {
	NODE* cursor = list->first;
	NODE* node = (NODE*) malloc(sizeof(NODE));
	task* t = (task*) malloc(sizeof(task));
	
	t->id = id;
	t->length = length;	
	node->task = t;
	node->next = NULL;

	printf("debug: before insertion of (id: %d, length: %d) => ", id, length);
	dumpList(list);

	if (!cursor) {
		list->first = node;
		list->last = node;
	}
	else if (cursor->task->length >= length) {

		node->next = cursor;
		list->first = node;
	}
	else {
		
		while (cursor && cursor->task->length < length)
			cursor = cursor->next;
			
		if (cursor) {
			node->next = cursor->next;
			cursor->next = node;
		}
	}

	printf("debug:  after insertion of (id: %d, length: %d) => ", id, length);
	dumpList(list);
}

void appendTask(LIST* list, int id, int length) {
	NODE* node = (NODE*) malloc(sizeof(NODE));
	task* t = (task*) malloc(sizeof(task));
	
	t->id = id;
	t->length = length;
	
	node->task = t;
	node->next = NULL;

	if (list->last)
		list->last->next = node;
		
	list->last = node;
	
	if (!list->first)
		list->first = list->last;
}

void removeTask(LIST* list, int id) {
	NODE* cursor = list->first;

	if (cursor->task->id == id) {
		list->first = cursor->next;
		free(cursor);
		if (!list->first)
			list->last = NULL;
	}
	else {
		while (cursor && cursor->next->task->id != id)
			cursor = cursor->next;
		
		if (cursor) {
			cursor->next = cursor->next->next;
			if (id == list->last->task->id)
				list->last = cursor;
		}
	}
}

void removeFirst(LIST* list) {
	if (list->first) {
		NODE* node = list->first;
		list->first = list->first->next;
		free(node);
	}
}

void dumpList(LIST* list) {
	NODE* cursor = list->first;
	
	while (cursor) {
		printf("(id: %d, length: %d) ", cursor->task->id, cursor->task->length);
		cursor = cursor->next;
	}
	
	printf("\n");
}