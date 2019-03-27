/*
 * _node.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
  unsigned char item;
  int priority;
  struct _node *next, *left, *right;
} node;

/******************************************************************************/
// Queue

node *add_sort(node *head) {
  node *previous = head;
  node *current = head->next;

  while ((current != NULL) && (head->priority > current->priority)) {
    previous = current;
    current = current->next;
  }

  if (head != previous) {
    node *aux = head;
    head = head->next;
    previous->next = aux;
    aux->next = current;
  }

  return head;
}

/******************************************************************************/
// Tree

void print_pre_order(node *tree, FILE *file) {
  if (tree != NULL) {
    fputc(tree->item, file);
    print_pre_order(tree->left, file);
    print_pre_order(tree->right, file);
  }
}

node *create_huffman_tree(node *head) {
  while (head->next != NULL) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = '*';
    new_node->priority = head->priority + head->next->priority;
    new_node->left = head;
    new_node->right = head->next;

    if (head->next->next != NULL) {
      node *aux = head->next->next;
      head->next->next = NULL;
      head->next = NULL;
      new_node->next = aux;
      head = new_node;
      head = add_sort(head);
    } else {
      head = new_node;
    }
  }
  return head;
}

int tree_size(node *root, int huff_tree_size) {
  if (root != NULL) {
    huff_tree_size++;
    huff_tree_size = tree_size(root->left, huff_tree_size);
    huff_tree_size = tree_size(root->right, huff_tree_size);
  }
  return huff_tree_size;
}




