/*
 * _compress.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef farias, joao paulo, milena nunes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_priority_queue.h"
#include "_hash_table.h"

#define SIZE_ARRAY 256

unsigned char set_bit (unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask | c;
}

int put_byte (hash_table *ht, FILE *file, FILE *compressed) {
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
  return pos_byte + 1;
}

void put_header (int *header, FILE *compressed) {
  unsigned char c = 0;
  int pos_byte = 7, indice = 0;

  for (indice = 0; indice < 16; indice++) {
    if (header[indice]) {
      c = set_bit (c, pos_byte);
    }

    pos_byte--;

    if (pos_byte < 0)
    {
      pos_byte = 7;
      fputc (c, compressed);
      c = 0;
    }
  }
}

int* create_header (int trash, int huff_tree_size) {
  int *header = (int*) malloc (16 * sizeof (int));

  for (int i = 2; i >= 0; i--) {
    header[i] = trash % 2;
    trash /= 2;
  }

  for (int i = 15; i >= 3; i--) {
    header[i] = huff_tree_size % 2;
    huff_tree_size /= 2;
  }
  return header;
}

void compress(hash_table *ht, priority_queue *pq, FILE *file, FILE *compressed) {
	int byte = 0, size, i;
	int frequency[SIZE_ARRAY] = {0};
	unsigned char way_tree[SIZE_ARRAY];

	while (byte != EOF) {
		byte = fgetc(file);
		frequency[byte]++;
	}

	for (i = 0; i < SIZE_ARRAY; i++) {
		if (frequency[i] > 0) {
			enqueue(pq, i, frequency[i]);
		}
	}

	pq->head = create_huffman_tree(pq->head);

	save_way(ht, pq->head, way_tree, 0);

	rewind(file);

	fputc (0, compressed);
	fputc (0, compressed);
	print_pre_order(pq->head, compressed);

	int trash = put_byte (ht, file, compressed);
	int huff_tree_size = tree_size (pq->head, 0);

	int *header = create_header (trash, huff_tree_size);

	rewind (compressed);

	put_header (header, compressed);
}

