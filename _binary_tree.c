/*
 * _binary_tree.c
 *
 *  Created on: 29 de mar de 2019
 *      Author: alef
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int TREE_SIZE_EXTRACTED = 0;

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

binary_tree *create_tree(binary_tree *bt, FILE *compressed,
                         unsigned char byte) {
  if (TREE_SIZE_EXTRACTED != 0) {
    byte = fgetc(compressed);
    TREE_SIZE_EXTRACTED--;

    if (byte == '*') {
      bt = create_binary_tree(byte, NULL, NULL);
      bt->left = create_tree(bt->left, compressed, byte);
      bt->right = create_tree(bt->right, compressed, byte);
    } else {
      if (byte == '\\') {
        byte = fgetc(compressed);
        TREE_SIZE_EXTRACTED--;
      }
      bt = create_binary_tree(byte, NULL, NULL);
    }
    return bt;
  }
  return bt;
}

void print_pre_order(binary_tree *bt) {
  if (bt != NULL) {
    printf("%c", bt->item);
    print_pre_order(bt->left);
    print_pre_order(bt->right);
  }
}
