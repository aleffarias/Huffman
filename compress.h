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

int is_bit_i_set(unsigned char c, int i);

unsigned char set_bit(unsigned char c, int i);

void print_byte(FILE *file, int array);

void compress(FILE *file, FILE *compress_file, node *root, int file_size);


#endif /* COMPRESS_H_ */
