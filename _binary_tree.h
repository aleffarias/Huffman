/*
 * _binary_tree.h
 *
 *  Created on: 29 de mar de 2019
 *      Author: alef
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

typedef struct _binary_tree binary_tree;

binary_tree *create_empty_binary_tree();

binary_tree *create_binary_tree(unsigned char item, binary_tree *left,
                                binary_tree *right);

binary_tree *create_tree(binary_tree *bt, FILE *compressed, unsigned char byte);

void print_pre_order(binary_tree *bt);

#endif /* BINARY_TREE_H_ */
