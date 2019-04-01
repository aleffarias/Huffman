#include <stdio.h>
#include <stdlib.h>


typedef struct _node {
	int item;
	struct _node *next;
} node;


node *create_linked_list();

int is_empty(node *head);

node *add_list(node *head, int item);

int search_list(node *head, int item);
