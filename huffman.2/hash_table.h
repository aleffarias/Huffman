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


hash_table *create_hash_table();

void put(hash_table *ht, int key, int size, unsigned char *way);
