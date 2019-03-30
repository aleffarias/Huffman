#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "priority_queue.h"


unsigned char set_bit (unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask | c;
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

int* create_header (int trash, int huff_tree) {
  int *header = (int*) malloc (16 * sizeof (int));

  for (int i = 2; i >= 0; i--) {
    header[i] = trash % 2;
    trash /= 2;
  }
  for (int i = 15; i >= 3; i--) {
    header[i] = huff_tree % 2;
    huff_tree /= 2;
  }
  return header;
}

int tree_size(node *tree, int size) {
  if (tree != NULL) {
    if (tree->left == NULL && tree->right == NULL && (tree->item == '*' || tree->item == '\\')) {
      size++;
    }
    size++;
    size = tree_size(tree->left, size);
    size = tree_size(tree->right, size);
  }
  return size;
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
  fputc(c, compressed);
  return pos_byte + 1;
}

void write_pre_order(node *tree, FILE *file) {
  if (tree != NULL) {
    if (tree->left == NULL && tree->right == NULL && (tree->item == '*' || tree->item == '\\')) {
      fputc('\\', file);
    }
    fputc(tree->item, file);
    write_pre_order(tree->left, file);
    write_pre_order(tree->right, file);
  }
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

node *sort(node *head) {
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
      head = sort(head);
    } else {
      head = new_node;
    }
  }
  return head;
}

void compress () {
  int byte = 0;
  int frequency[ARRAY_SIZE] = {0};
  unsigned char way_tree[ARRAY_SIZE];
  char my_file[50];

  puts ("Qual arquivo deseja comprimir?\nInsira: arquivo.extensao");
  scanf ("%s", my_file);
  FILE *file = fopen(my_file, "r");

  if (file == NULL) {
    puts("\nFile error\n");
    return;
  }

  puts ("\nNao vai durar nem uma hora!\n.\n.\n.");

  while (byte != EOF) {
    byte = fgetc(file);
    frequency[byte]++;
  }

  FILE *compressed = fopen("compressed_file.huff", "w+");
  priority_queue *pq = create_priority_queue();
  hash_table *ht = create_hash_table();

  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (frequency[i] > 0) {
      enqueue(pq, i, frequency[i]);
    }
  }

  pq->head = create_huffman_tree(pq->head);

  save_way(ht, pq->head, way_tree, 0);

  rewind(file);

  fputc (0, compressed);
  fputc (0, compressed);

  write_pre_order(pq->head, compressed);

  int trash = put_byte (ht, file, compressed);
  int huff_tree = tree_size (pq->head, 0);
  int *header = create_header (trash, huff_tree);

  rewind (compressed);

  put_header (header, compressed);

  fclose (file);
  fclose (compressed);

  puts ("Concluido!\n");
}
