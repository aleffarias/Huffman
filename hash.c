/*
 * hash.c
 *
 *  Created on: 15 de mar de 2019
 *      Author: alef
 */

#include <stdio.h>
#include <stdlib.h>

#include "compress.h"
#include "extract.h"
#include "hash.h"
#include "queue.h"
#include "tree.h"

#define SIZE_TABLE 256

typedef struct _element {
  int *value;
} element;

typedef struct _hash_table {
  element *table[SIZE_TABLE];
} hash_table;

hash_table *create_hash_table() {
  hash_table *new_ht = (hash_table *)malloc(sizeof(hash_table));
  for (int i = 0; i < SIZE_TABLE; i++) {
    new_ht->table[i] = NULL;
  }
  return new_ht;
}