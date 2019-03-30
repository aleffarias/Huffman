#include <stdio.h>
#include <stdlib.h>

typedef struct _binary_tree {
  unsigned char item;
  struct _binary_tree *left, *right;
} binary_tree;

binary_tree *create_empty_binary_tree() { return NULL; }

binary_tree *create_binary_tree(unsigned char item, binary_tree *left,
                                binary_tree *right) {
  binary_tree *new_bt = (binary_tree *)malloc(sizeof(binary_tree));
  new_bt->item = item;
  new_bt->left = left;
  new_bt->right = right;
  return new_bt;
}

void print_pre_order(binary_tree *bt) {
  if (bt != NULL) {
    printf("%c", bt->item);
    print_pre_order(bt->left);
    print_pre_order(bt->right);
  }
}
