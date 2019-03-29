/*
 * _compress.h
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#ifndef COMPRESS_H_
#define COMPRESS_H_

typedef struct _node node;
typedef struct _priority_queue priority_queue;
typedef struct _element element;
typedef struct _hash_table hash_table;

void write_pre_order(node *tree, FILE *file);

int tree_size(node *tree, int size);

void save_way(hash_table *ht, node *tree, unsigned char *way, int pos);

unsigned char set_bit(unsigned char c, int i);

int put_byte(hash_table *ht, FILE *file, FILE *compressed);

void put_header(int *header, FILE *compressed);

int *create_header(int trash, int huff_tree);

void compress();

#endif /* COMPRESS_H_ */
