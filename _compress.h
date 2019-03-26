/*
 * _compress.h
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#ifndef COMPRESS_H_
#define COMPRESS_H_

unsigned char set_bit (unsigned char c, int i);

int put_byte (hash_table *ht, FILE *file, FILE *compressed);

void put_header (int *header, FILE *compressed);

int* create_header (int trash, int huff_tree_size);

void compress(hash_table *ht, node *head, FILE *file, FILE *compressed);

#endif /* COMPRESS_H_ */
