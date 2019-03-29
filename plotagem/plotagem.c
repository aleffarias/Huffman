#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cont_list = 0, cont_tree = 0;

typedef struct node node;
typedef struct binary_tree binary_tree;

// List
struct node {
  int item;
  node *next;
};

node *create_linked_list() {
  return NULL; 
}

node *add_list(node *head, int item) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->item = item;
  new_node->next = head;

  return new_node;
}

node *search_list(node *head, int item) {
  node *aux = head;
  while (head != NULL) {
    if (head->item == item) {
      return head;
    }
    head = head->next;
    cont_list++;
  }

  return aux;
}

int is_empty(node *head) { return (head == NULL); }

void print_linked_list(node *head) {
  while (head != NULL) {
    printf("%d ", head->item);
    head = head->next;
  }
}

void print_linked_list_recursively(node *head) {
  if (!is_empty(head)) {
    printf("%d\n", head->item);
    print_linked_list(head->next);
  }
}

// Tree

struct binary_tree {
  int item;
  binary_tree *left;
  binary_tree *right;
};

binary_tree* create_empty_binary_tree()
{
  return NULL;
}

binary_tree* create_binary_tree(
  int item, binary_tree *left, binary_tree *right)
  {
  binary_tree *new_binary_tree =
  (binary_tree*) malloc(sizeof(binary_tree));
  new_binary_tree->item = item;
  new_binary_tree->left = left;
  new_binary_tree->right = right;

  return new_binary_tree;
}

binary_tree* add_tree(binary_tree *bt, int item)
{
  if (bt == NULL) {
    bt = create_binary_tree(item, NULL, NULL);
  } else if (bt->item > item) {
    bt->left = add_tree(bt->left, item);
  } else {
    bt->right = add_tree(bt->right, item);
  }

  return bt;
}

binary_tree* search_tree(binary_tree *bt, int item)
{
  if ((bt == NULL) || (bt->item == item)) {
    return bt;
  } else if (bt->item > item) {
    cont_tree++;
    return search_tree(bt->left, item);
  } else {
    cont_tree++;
    return search_tree(bt->right, item);
  }
}

int main () {
  int i, jp, max, add_l, add_t;
  
  node *list = create_linked_list();
  binary_tree *bt = create_empty_binary_tree();

  FILE *tree_file = fopen("tree.txt", "w+");
  FILE *list_file = fopen("list.txt", "w+");

  printf("Digite a quantidade de números:\n");
  scanf("%d", &max);

  printf("intervalo da rand: [0,%d]\n", max);

  srand(time(NULL));

  // ADD
  for(i = 1; i <= max; i++) { 
    jp = rand() % 1000000;
    printf("%d ", jp);
    
    
    list = add_list(list, jp);
    bt = add_tree(bt, jp);
  }
  printf("\n");

  // Search
  for(i = 1; i <= max; i++) { 
    jp = rand() % 1000000;
    
    list = search_list(list, jp);
    fprintf(list_file, "%d %d\n",jp, cont_list);
    cont_list = 0;

    search_tree(bt, jp);
    fprintf(tree_file, "%d %d\n",jp, cont_tree);
    cont_tree = 0;

  }
  print_linked_list(list);
  printf("\n");
  fclose(tree_file);
  fclose(list_file);
  return 0;
}
