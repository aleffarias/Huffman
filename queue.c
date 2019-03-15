/*
 * queue.c
 *
 *  Created on: 15 de mar de 2019
 *      Author: alef, milena, joao paulo
 */
#include <stdio.h>
#include <stdlib.h>

#include "compress.h"
#include "extract.h"
#include "queue.h"
#include "tree.h"
#include "hash.h"


typedef struct _node
{
	char item;
	int priority;
	struct _node *next, *left, *right;
} node;

typedef struct _priority_queue
{
	node *head;
} priority_queue;

int is_empty (priority_queue *queue)
{
	return (queue->head == NULL);
}

priority_queue* create_priority_queue ()
{
	 priority_queue *new_pq = (priority_queue*) malloc (sizeof (priority_queue));
	 return new_pq;
}

void enqueue (priority_queue *pq, char i, int p)
{
	node *new_node = (node*) malloc (sizeof (node));
	new_node->item = i;
	new_node->priority = p;
	if (is_empty(pq) || (p <= pq->head->priority))
	{

		new_node->next = pq->head;
		pq->head = new_node;
	}
	else
	{
		node *current = pq->head;
		while ((current->next != NULL) && (current->next->priority < new_node->priority))
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}

void print_queue (priority_queue *pq)
{
	node *aux = pq->head;
	while (aux != NULL)
	{
		printf ("%c ", aux->item);
		aux = aux->next;
	}
}

priority_queue *add_sort (priority_queue *pq)
{
	node *current = pq->head->next;
	node *previous = pq->head;

	while ((current != NULL) && (pq->head->priority > current->priority))
	{
		previous = current;
		current = current->next;
	}
	if(pq->head != previous) {
		node *aux = pq->head;
		pq->head = pq->head->next;
		previous->next = aux;
		aux->next = current;
	}

	return pq;
}

