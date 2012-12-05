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

/**
 *  insert task in sorted order (by length, asc)
 */
void insertTask(LIST* list, int id, int length);

/* 
 *  append task to end of list
 */
void appendTask(LIST* list, int id, int length);

/*
 *  append node to end of list
 */ 
void appendNode(LIST* list, NODE* node);

/*
 *  remove task from (anywhere within) list
 */
void removeTask(LIST* list, int id);

/*
 *  cut first node off list
 */
NODE* removeFirst(LIST* list);

#endif
