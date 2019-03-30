#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 256
#define ARRAY_SIZE 256

typedef struct _element {
  int size;
  unsigned char way[HASH_SIZE];
} element;

typedef struct _hash_table {
  element *table[HASH_SIZE];
} hash_table;


hash_table *create_hash_table() {
  hash_table *new_ht = (hash_table *)malloc(sizeof(hash_table));

  for (int i = 0; i < HASH_SIZE; i++) {
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
