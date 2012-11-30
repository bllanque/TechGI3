#include <stdlib.h>
#include <stdio.h>

#include "tasklist.h"
#include "system.h"

void insertTask(LIST* list, task* t) {
}

void appendTaskByID(LIST* list, int id, int length) {
	printf("debug: appendTaskByID: entering\n");

	task* t = (task*) malloc(sizeof(task));
	
	t->id = id;
	t->length = length;
	
	appendTask(list, t);
	printf("debug: appendTaskByID: leaving\n");
}

void appendTask(LIST* list, task* t) {
	printf("debug: appendTask: entering\n");

	NODE* node = (NODE*) malloc(sizeof(NODE));

	node->task = t;
	node->next = NULL;

	if (list->last)
		list->last->next = node;
		
	list->last = node;
	
	if (!list->first)
		list->first = list->last;

	printf("debug: appendTask: leaving\n");
}

void removeRightNode(LIST* list, NODE* node) {
	printf("debug: removeRightTask: entering\n");
	
	NODE* temp = node->next;

	node->next = node->next->next;

	free(temp);

	printf("debug: removeRightTask: leaving\n");
}

void removeTaskById(LIST* list, int id) {
	printf("debug: removeTaskById: entering\n");

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
			removeRightNode(list, cursor);
			cursor->next = cursor->next->next;
			if (id == list->last->task->id)
				list->last = cursor;
		}
	}
	
	printf("debug: removeTaskById: leaving\n");
}
