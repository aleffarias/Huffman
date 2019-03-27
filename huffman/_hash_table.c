/*
 * _hash_table.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_element.h"

#define SIZE_HASH 256

typedef struct _hash_table {
  element *table[SIZE_HASH];
} hash_table;

/******************************************************************************/
// Hash_table

hash_table *create_hash_table() {
  hash_table *new_ht = (hash_table *)malloc(sizeof(hash_table));

  for (int i = 0; i < SIZE_HASH; i++) {
    new_ht->table[i] = NULL;
  }
  return new_ht;
}

void put(hash_table *ht, int key, int size, unsigned char *way) {
  element *new_element = (element *)malloc(sizeof(element));
  new_element->size = size;

  for (int i = 0; i < size; i++) {
    new_element->way[i] = way[i];
  }
  ht->table[key] = new_element;
}

void save_way(hash_table *ht, node *tree, unsigned char *way, int pos) {
  if (tree->left != NULL) {
    way[pos] = '0';
    save_way(ht, tree->left, way, pos + 1);
  }

  if (tree->right != NULL) {
    way[pos] = '1';
    save_way(ht, tree->right, way, pos + 1);
  }

  if ((tree->left == NULL) && (tree->right == NULL)) {
    put(ht, tree->item, pos, way);
  }
}



