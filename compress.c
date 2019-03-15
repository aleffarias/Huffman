/*
 * compress.c
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

typedef struct _node {
  char item;
  int priority;
  struct _node *next, *left, *right;
} node;

typedef struct _priority_queue {
  node *head;
} priority_queue;

typedef struct _element {
  int *value;
} element;

typedef struct _hash_table {
  element *table[SIZE_TABLE];
} hash_table;

#define MAX 100

int is_bit_i_set(unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask & c;
}

unsigned char set_bit(unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask | c;
}

void print_byte(FILE *file, int array) {
  int cont, caracter;
  for (cont = 7; cont >= 0; cont--) {
    set_bit(caracter, cont);
    if (cont == 0) {
      fputc(caracter, file);
      cont = 7;
      caracter = 0;
    }
  }
}

void put(hash_table *ht, int key, int *value, int h_tree) {
  element *new_element = (element *)malloc(sizeof(element * h_tree));
  new_element->value = value;
  ht->table[key] = new_element;
}

int *get(hash_table *ht, int key) { return ht->table[key]->value; }

void get_way(node *huff_tree, hash_table *ht, int i, int x, int h_tree,
             int *array) {
  if (huff_tree != NULL) {
    array[i] = x;
    if (huff_tree->item != '*') {
      put(ht, huff_tree->item, array, h_tree);
    }
    get_way(huff_tree->left, ht, i + 1, 0, h_tree, array);
    get_way(huff_tree->right, ht, i + 1, 1, h_tree, array);
  }
}

void compress(FILE *file, FILE *compress_file, node *root, hash_table *ht) {
  int array[MAX], height;
  fputc(0, compress_file);
  fputc(0, compress_file);
  height = h(root);
  get_way(root, ht, 0, 0, height, array);
}
