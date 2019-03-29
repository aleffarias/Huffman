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

typedef struct _element {
  int size;
  unsigned char way[256];
} element;

typedef struct _hash_table {
  element *table[256];
} hash_table;

hash_table *create_hash_table() {
  hash_table *new_ht = (hash_table *)malloc(sizeof(hash_table));

  for (int i = 0; i < 256; i++) {
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
