/*
 * _compress.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef farias, joao paulo, milena nunes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_hash_table.h"
#include "_node.h"
#include "_priority_queue.h"

#define ARRAY_SIZE 256
#define HASH_SIZE 256

typedef struct _node {
  unsigned char item;
  int priority;
  struct _node *next, *left, *right;
} node;

typedef struct _priority_queue {
  node *head;
} priority_queue;

typedef struct _element {
  int size;
  unsigned char way[HASH_SIZE];
} element;

typedef struct _hash_table {
  element *table[HASH_SIZE];
} hash_table;

void write_pre_order(node *tree, FILE *file) {
  if (tree != NULL) {
    if (tree->left == NULL && tree->right == NULL &&
        (tree->item == '*' || tree->item == '\\')) {
      fputc('\\', file);
    }
    fputc(tree->item, file);
    write_pre_order(tree->left, file);
    write_pre_order(tree->right, file);
  }
}

int tree_size(node *tree, int size) {
  if (tree != NULL) {
    if (tree->left == NULL && tree->right == NULL &&
        (tree->item == '*' || tree->item == '\\')) {
      size++;
    }
    size++;
    size = tree_size(tree->left, size);
    size = tree_size(tree->right, size);
  }
  return size;
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

unsigned char set_bit(unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask | c;
}

int put_byte(hash_table *ht, FILE *file, FILE *compressed) {
  int byte = fgetc(file);
  unsigned char c = 0;
  int pos_byte = 7, pos_way = 0;

  while (byte != EOF) {
    if (pos_way < ht->table[byte]->size) {
      if (ht->table[byte]->way[pos_way] == '1') {
        c = set_bit(c, pos_byte);
      }
      pos_way++;
      pos_byte--;
    } else {
      pos_way = 0;
      byte = fgetc(file);
    }
    if (pos_byte < 0) {
      pos_byte = 7;
      fputc(c, compressed);
      c = 0;
    }
  }
  fputc(c, compressed);
  return pos_byte + 1;
}

void put_header(int *header, FILE *compressed) {
  unsigned char c = 0;
  int pos_byte = 7, indice = 0;

  for (indice = 0; indice < 16; indice++) {
    if (header[indice]) {
      c = set_bit(c, pos_byte);
    }

    pos_byte--;

    if (pos_byte < 0) {
      pos_byte = 7;
      fputc(c, compressed);
      c = 0;
    }
  }
}

int *create_header(int trash, int huff_tree) {
  int *header = (int *)malloc(16 * sizeof(int));
  int i;
  for (i = 2; i >= 0; i--) {
    header[i] = trash % 2;
    trash /= 2;
  }

  for (i = 15; i >= 3; i--) {
    header[i] = huff_tree % 2;
    huff_tree /= 2;
  }

  return header;
}

void compress() {
  int byte = 0, i;
  int frequency[ARRAY_SIZE] = {0};
  unsigned char way_tree[ARRAY_SIZE];

  FILE *file = fopen("huffman.pdf", "r");

  if (file == NULL) {
    puts("File error\n");
    return;
  }

  while (byte != EOF) {
    byte = fgetc(file);
    frequency[byte]++;
  }

  FILE *compressed = fopen("compressed_file.huff", "w+");
  priority_queue *pq = create_priority_queue();
  hash_table *ht = create_hash_table();

  for (i = 0; i < ARRAY_SIZE; i++) {
    if (frequency[i] > 0) {
      enqueue(pq, i, frequency[i]);
    }
  }

  pq->head = create_huffman_tree(pq->head);

  save_way(ht, pq->head, way_tree, 0);

  rewind(file);

  fputc(0, compressed);
  fputc(0, compressed);

  write_pre_order(pq->head, compressed);

  int trash, huff_tree;

  trash = put_byte(ht, file, compressed);
  huff_tree = tree_size(pq->head, 0);

  int *header = create_header(trash, huff_tree);

  rewind(compressed);

  put_header(header, compressed);

  fclose(file);
  fclose(compressed);

  puts("Operacao realizada com sucesso!\n");
}
