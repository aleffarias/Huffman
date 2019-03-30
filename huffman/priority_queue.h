#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
  unsigned char item;
  int priority;
  struct _node *next, *left, *right;
} node;

typedef struct _priority_queue {
  node *head;
} priority_queue;


priority_queue *create_priority_queue();

int is_empty_pq(priority_queue *pq);

void enqueue(priority_queue *pq, char i, int p);

