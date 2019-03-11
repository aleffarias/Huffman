#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

priority_queue *add_sort (priority_queue *pq, node* new_node)
{
	
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

/*void print_queue (priority_queue *pq)
{
	node *aux = pq->head;
	while (aux != NULL)
	{
		printf ("%c ", aux->item);
		aux = aux->next;
	}
}

void print_pre_order(node *pq)
{	
	if (pq != NULL) {
		printf(" %c ", pq->item);
		print_pre_order(pq->left);
		print_pre_order(pq->right);
	}
}*/

node* create_huffman_tree (priority_queue *pq)
{
	while (pq->head->next != NULL)
	{
		node *new_node = (node*) malloc (sizeof(node));
		new_node->item = '*';
		new_node->priority = pq->head->priority + pq->head->next->priority; 
		new_node->left = pq->head;
		new_node->right = pq->head->next;

		if(pq->head->next->next != NULL) 
		{
			node *aux = pq->head->next->next;
			pq->head->next->next = NULL;
			pq->head->next = NULL;
			new_node->next = aux;
			pq->head = new_node;

			pq = add_sort (pq);
		} else {
			pq->head = new_node;
		}
	}
}


int main ()
{
	int i, priority;
	char item;
	priority_queue *pq = create_priority_queue ();
	for(i = 0; i < 6; i++) {
		scanf("%c%d", &item, &priority);
		getchar();
		enqueue(pq, item, priority);

	} 
	create_huffman_tree(pq);

	return 0;
}
