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

  node *create_huffman_tree(node * head) {
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

  return head;
}