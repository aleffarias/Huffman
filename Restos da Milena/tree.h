/*
 * tree.h
 *
 *  Created on: 15 de mar de 2019
 *      Author: alef
 */

#ifndef TREE_H_
#define TREE_H_

typedef struct _node node;

typedef struct _priority_queue priority_queue;

void print_pre_order(node *pq, FILE *file);

void create_huffman_tree(priority_queue *pq);

void tree_size(node *root);

int max(int a, int b);

int h(node *bt);

#endif /* TREE_H_ */
