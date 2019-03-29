/*
 * extract.h
 *
 *  Created on: 29 de mar de 2019
 *      Author: alef
 */

#ifndef EXTRACT_H_
#define EXTRACT_H_

int power(int a, int b);

int is_bit_i_set(unsigned char c, int i);

void calc_tree_size(binary_tree *bt, FILE *compressed);

void write_file(binary_tree *bt, FILE *compressed, FILE *extracted,
                long int file_size);

void decompress();

#endif /* EXTRACT_H_ */
