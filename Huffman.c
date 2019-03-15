/*
 ============================================================================
 Name        : Huffman.c
 Author      : Milena, Alef e Joao Paulo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
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

int main() {
	int caracter = 0, size;
	int array[256] = {0};
	FILE *arquivo = fopen("huffinho.txt", "r");
	FILE *compress_file = fopen("compressed.txt", "w+");

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
	/*tree_size(pq->head);
	fseek(arquivo, 0, SEEK_END);
	size = ftell(arquivo);
	rewind(arquivo);
	compress(arquivo, compress_file, pq->head, size);*/
	print_pre_order(pq->head, compress_file);
	//printf("%d\n", huff_tree_size);
	/*create_huffman_tree(pq);
	for(int i = 0; i < size; i++) {
	}*/
	return 0;

}
