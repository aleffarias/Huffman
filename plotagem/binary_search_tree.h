#include <stdio.h>
#include <stdlib.h>


typedef struct _binary_tree {
	int item;
	struct _binary_tree *left;
	struct _binary_tree *right;
} binary_tree;


binary_tree* create_empty_binary_tree();

binary_tree* create_binary_tree(int item, binary_tree *left,
								binary_tree *right);

binary_tree* add_tree(binary_tree *bt, int item);

int search_tree(binary_tree *bt, int item);
