#include <stdio.h>
#include <stdlib.h>

typedef struct _binary_tree {
  unsigned char item;
  struct _binary_tree *left, *right;
} binary_tree;

binary_tree *create_empty_binary_tree();

binary_tree *create_binary_tree(unsigned char item, binary_tree *left,
                                binary_tree *right);

void print_pre_order(binary_tree *bt);
