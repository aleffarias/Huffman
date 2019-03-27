/*
 * _node.h
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#ifndef NODE_H_
#define NODE_H_

typedef struct _node node;

/******************************************************************************/
// Queue

node *add_sort(node *head);

/******************************************************************************/
// Tree

void print_pre_order(node *tree, FILE *file);

node *create_huffman_tree(node *head);

int tree_size(node *root, int huff_tree_size);

#endif /* NODE_H_ */
