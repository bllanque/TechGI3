#ifndef TASKLIST_H
#define TASKLIST_H

#include "vorgabe.h"

/**
 *	singly linked list node type
 */
typedef struct node_t {
	struct task_t *task;
	struct node_t *next;	
} NODE;

/**
 *	singly linked list (anchor) type
 */
typedef struct list_s {
	struct node_t *first;
	struct node_t *last;
} LIST;

void insertTask(LIST* list, task* t);

void appendTaskByID(LIST* list, int id, int length);

void appendTask(LIST* list, task* t);

void removeTaskById(LIST* list, int id);

void removeRightNode(LIST* list, NODE* node);

#endif