#include <stdlib.h>
#include <stdio.h>

#include "tasklist.h"
#include "system.h"

void insertTask(LIST* list, int id, int length) {
	NODE* cursor = list->first;
	NODE* node = (NODE*) malloc(sizeof(NODE));
	task* t = (task*) malloc(sizeof(task));
	
	t->id = id;
	t->length = length;	
	node->task = t;
	node->next = NULL;

	if (!cursor) {
		list->first = node;
		list->last = node;
	}
	else {
		
		while (cursor && cursor->task->length <= length)
			cursor = cursor->next;
			
		if (cursor) {
			node->next = cursor->next;
			cursor->next = node;
			if (node->next == NULL)
				list->last = node;
		}
		else {
			if (list->last->task->id != id) {
				list->last->next = node;
				list->last = node;
			}
		}
	}
}

void appendTask(LIST* list, int id, int length) {
	NODE* node = (NODE*) malloc(sizeof(NODE));
	task* t = (task*) malloc(sizeof(task));
	
	t->id = id;
	t->length = length;
	
	node->task = t;
	node->next = NULL;

	appendNode(list, node);
}

void appendNode(LIST* list, NODE* node) {
	if (node) {
		if (list->first)
			list->last->next = node;
		else
			list->first = node;
			
		list->last = node;
	}
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

NODE* removeFirst(LIST* list) {
	NODE* node = list->first;

	if (node) {
		list->first = node->next;
		node->next = NULL;
	}

	return node;
}

void dumpList(LIST* list) {
	NODE* cursor = list->first;
	
	while (cursor && cursor->task) {
		printf("(id: %d, length: %d) ", cursor->task->id, cursor->task->length);
		cursor = cursor->next;
	}
	
	printf("\n");
}
