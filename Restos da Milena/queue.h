/*
 * queue.h
 *
 *  Created on: 15 de mar de 2019
 *      Author: alef
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct _node node;

typedef struct _priority_queue priority_queue;

int is_empty (priority_queue *queue);

priority_queue* create_priority_queue ();

void enqueue (priority_queue *pq, char i, int p);

void print_queue (priority_queue *pq);

priority_queue *add_sort (priority_queue *pq);




#endif /* QUEUE_H_ */
