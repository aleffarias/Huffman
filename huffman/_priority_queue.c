/*
 * _priority_queue.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_node.h"

typedef struct _priority_queue {
  node *head;
} priority_queue;

/******************************************************************************/
// Queue

priority_queue *create_priority_queue() {
  priority_queue *new_pq = (priority_queue *)malloc(sizeof(priority_queue));
  new_pq->head = NULL;
  return new_pq;
}

int is_empty_pq(priority_queue *pq) { return (pq->head == NULL); }

void enqueue(priority_queue *pq, char i, int p) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->item = i;
  new_node->priority = p;

  if ((is_empty_pq(pq)) || (p <= pq->head->priority)) {
    new_node->next = pq->head;
    pq->head = new_node;
  } else {
    node *current = pq->head;

    while ((current->next != NULL) &&
           (current->next->priority < new_node->priority)) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

