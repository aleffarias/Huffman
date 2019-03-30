#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "priority_queue.h"

unsigned char set_bit (unsigned char c, int i);

void put_header (int *header, FILE *compressed);

int* create_header (int trash, int huff_tree);

int tree_size(node *tree, int size);

int put_byte (hash_table *ht, FILE *file, FILE *compressed);

void write_pre_order(node *tree, FILE *file);

node *sort(node *head);
  
node *create_huffman_tree(node *head);

void compress ();
