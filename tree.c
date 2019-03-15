/*
 * tree.c
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

int huff_tree_size = 0;

typedef struct _node {
  char item;
  int priority;
  struct _node *next, *left, *right;
} node;

typedef struct _priority_queue {
  node *head;
} priority_queue;

void print_pre_order(node *pq, FILE *file) {
  if (pq != NULL) {
    fputc(pq->item, file);
    print_pre_order(pq->left, file);
    print_pre_order(pq->right, file);
  }
}

void create_huffman_tree(priority_queue *pq) {
  while (pq->head->next != NULL) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = '*';
    new_node->priority = pq->head->priority + pq->head->next->priority;
    new_node->left = pq->head;
    new_node->right = pq->head->next;

    if (pq->head->next->next != NULL) {
      node *aux = pq->head->next->next;
      pq->head->next->next = NULL;
      pq->head->next = NULL;
      new_node->next = aux;
      pq->head = new_node;

      pq = add_sort(pq);
    } else {
      pq->head = new_node;
    }
  }
}

void tree_size(node *root) {
  if (root != NULL) {
    huff_tree_size++;
    tree_size(root->left);
    tree_size(root->right);
  }
}

int max(int a, int b) { return (a > b) ? a : b; }

int h(node *bt) {
  if (bt == NULL) {
    return -1;
  } else {
    return 1 + max(h(bt->left), h(bt->right));
  }
}
