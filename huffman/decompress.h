#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"


int is_bit_i_set(unsigned char c, int i);

void write_file(binary_tree *bt, FILE *compressed, FILE *extracted, unsigned long long int file_size);

binary_tree *create_tree(binary_tree *bt, FILE *compressed, unsigned char byte);

int power(int a, int b);

void calc_tree_size(binary_tree *bt, FILE *compressed);

void decompress ();
