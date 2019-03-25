#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

int huff_tree_size = 0;

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

void print_pre_order(node *pq, FILE *file)
{
	if (pq != NULL) {
		fputc(pq->item, file);
		print_pre_order(pq->left, file);
		print_pre_order(pq->right, file);
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

void tree_size(node *root) {
    if(root != NULL) {
        huff_tree_size++;
        tree_size(root->left);
        tree_size(root->right);
    }
}

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask & c;
}

unsigned char set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return mask | c;
}

void print_byte(FILE *file, int array) {
	int cont;
	for(cont = 7; cont >= 0; cont--) {
		set_bit(caracter, cont);
		if(cont == 0) {
			fputc(caracter, file);
			cont = 7;
			caracter = 0;
		}
	}
}

void compress(FILE *file, FILE *compress_file, node *root, int file_size) {
	int array[MAX];
	fputc(0, compress_file);
	fputc(0, compress_file);
	unsigned char caracter;
	print_pre_order(root, compress_file);
	while(caracter != EOF){
		
	}
}

int main ()
{
	int caracter = 0, size;
  	int array[256] = {0};
	FILE *arquivo = fopen("huffmando.txt", "r");
	FILE *compress_file = fopen("compress.txt", "w+");

	if (arquivo == NULL) {
		printf("File error\n");
		return 0;
	}

  	while(caracter != EOF) {
  		caracter = fgetc(arquivo);
  		array[caracter]++;

  	}

	int i, priority;
	char item;
	priority_queue *pq = create_priority_queue ();
	for(i = 0; i < 256; i++) {
		if(array[i] > 0) {
			enqueue(pq, i, array[i]);
		}
	}
    create_huffman_tree(pq);
	tree_size(pq->head);
	fseek(arquivo, 0, SEEK_END);
	size = ftell(arquivo);
	rewind(arquivo);
	compress(arquivo, compress_file, pq->head, size);
	//print_pre_order(pq->head);
	//printf("%d\n", huff_tree_size);
	/*create_huffman_tree(pq);
	for(int i = 0; i < size; i++) {
	}*/

	return 0;
}
