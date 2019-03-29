/*
 * _priority_queue.h
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

typedef struct _priority_queue priority_queue;

priority_queue *create_priority_queue();

int is_empty_pq(priority_queue *pq);

void enqueue(priority_queue *pq, char i, int p);

#endif /* PRIORITY_QUEUE_H_ */
