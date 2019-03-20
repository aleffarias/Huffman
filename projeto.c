#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_HASH 256
#define SIZE_ARRAY 256
/******************************************************************************/
// Structs

typedef struct _node {
  char item;
  int priority;
  struct _node *next, *left, *right;
} node;

typedef struct _priority_queue {
  node *head;
} priority_queue;

typedef struct _element {
  int size;
  unsigned char way[SIZE_HASH];
} element;

typedef struct _hash_table {
  element *table[SIZE_HASH];
} hash_table;

/******************************************************************************/
// Queue

priority_queue *create_priority_queue() {
  priority_queue *new_pq = (priority_queue *)malloc(sizeof(priority_queue));
  new_pq->head = NULL;
  return new_pq;
}

int is_empty_pq(priority_queue *pq) { return (pq->head == NULL); }

void enqueue(priority_queue *pq, char i, int p) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->item = i;
  new_node->priority = p;

  if ((is_empty_pq(pq)) || (p <= pq->head->priority)) {
    new_node->next = pq->head;
    pq->head = new_node;
  } else {
    node *current = pq->head;

    while ((current->next != NULL) &&
           (current->next->priority < new_node->priority)) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

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

void tree_size(node *root, int huff_tree_size) {
  if (root != NULL) {
    huff_tree_size++;
    tree_size(root->left, huff_tree_size);
    tree_size(root->right, huff_tree_size);
  }
}

/******************************************************************************/
// Hash_table

hash_table *create_hash_table() {
  hash_table *new_ht = (hash_table *)malloc(sizeof(hash_table));

  for (int i = 0; i < SIZE_HASH; i++) {
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

void print_way(element *element) {
  for (int i = 0; i < element->size; i++) {
    printf("%c", element->way[i]);
  }
  puts("\n");
}
/******************************************************************************/

unsigned char set_bit(unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask | c;
}

void compress(hash_table *ht, FILE *file, FILE *compressed) {
  int byte = fgetc(file);
  unsigned char c = 0;
  int i = 7, j = 0;

  while (byte != EOF) {
    if (j < ht->table[byte]->size) {
      if (ht->table[byte]->way[j] == '1') {
        c = set_bit(c, i);
      }
      j++;
      i--;
    } else {
      j = 0;
      byte = fgetc(file);
    }
    if (i < 0) {
      putchar(c);
      i = 7;
      fputc(c, compressed);
      c = 0;
    }
  }
}

int main() {
  int byte = 0, size, i;
  int frequency[SIZE_ARRAY];
  FILE *file = fopen("huffman.txt", "r");

  if (file == NULL) {
    puts("File error");
    return 0;
  }

  for (int j = 0; j < SIZE_ARRAY; j++) {
    frequency[j] = 0;
  }

  FILE *compressed = fopen("compress_file.txt", "w+");

  while (byte != EOF) {
    byte = fgetc(file);
    frequency[byte]++;
  }

  priority_queue *pq = create_priority_queue();
  hash_table *ht = create_hash_table();

  for (i = 0; i < SIZE_ARRAY; i++) {
    if (frequency[i] > 0) {
      enqueue(pq, i, frequency[i]);
    }
  }

  pq->head = create_huffman_tree(pq->head);
  // print_pre_order(pq->head, compressed);

  // aqui vamos chamar a funcao de salvar o caminho da arvore
  unsigned char way_tree[SIZE_ARRAY];
  save_way(ht, pq->head, way_tree, 0);
  rewind(file);

  // for (i = 0; i < SIZE_HASH; i++) {
  //   if (ht->table[i] != NULL) {
  //     print_way(ht->table[i]);
  //   }
  // }

  compress(ht, file, compressed);

  fclose(file);
  fclose(compressed);

  return 0;
}