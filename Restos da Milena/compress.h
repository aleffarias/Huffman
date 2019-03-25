/*
 * compress.h
 *
 *  Created on: 15 de mar de 2019
 *      Author: alef
 */

#ifndef COMPRESS_H_
#define COMPRESS_H_

typedef struct _node node;

typedef struct _priority_queue priority_queue;

typedef struct _element element;

typedef struct _hash_table hash_table;

int is_bit_i_set(unsigned char c, int i);

unsigned char set_bit(unsigned char c, int i);

void print_byte(FILE *file, int array);

void put(hash_table *ht, int key, int *value, int h_tree);

int *get(hash_table *ht, int key);

void get_way(node *huff_tree, hash_table *ht, int i, int x, int h_tree,
             int *array);

void compress(FILE *file, FILE *compress_file, node *root, hash_table *ht);

#endif /* COMPRESS_H_ */
