#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tree_size = 0;
int trash_size = 0;

typedef struct _binary_tree {
  unsigned char item;
  struct _binary_tree *left, *right;
} binary_tree;

int powow(int a, int b) {
  int base = a;
  if (b == 0) {
    return 1;
  }
  for (int i = 1; i < b; i++) {
    a *= base;
  }
  return a;
}

binary_tree *create_empty_binary_tree() { return NULL; }

binary_tree *create_binary_tree(unsigned char item, binary_tree *left,
                                binary_tree *right) {
  binary_tree *new_bt = (binary_tree *)malloc(sizeof(binary_tree));
  new_bt->item = item;
  new_bt->left = left;
  new_bt->right = right;
  return new_bt;
}

binary_tree *create_tree(binary_tree *bt, FILE *compressed,
                         unsigned char byte) {
  if (tree_size != 0) {
    byte = fgetc(compressed);
    tree_size--;

    if (byte == '*') {
      bt = create_binary_tree(byte, NULL, NULL);
      bt->left = create_tree(bt->left, compressed, byte);
      bt->right = create_tree(bt->right, compressed, byte);
    } else {
      if (byte == '/') {
        byte = fgetc(compressed);
        tree_size--;
      }
      bt = create_binary_tree(byte, NULL, NULL);
    }
    return bt;
  }
}

int is_bit_i_set(unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask & c;
}

void print_pre_order(binary_tree *bt) {
  if (bt != NULL) {
    printf("%c ", bt->item);
    print_pre_order(bt->left);
    print_pre_order(bt->right);
  }
}

void calc_tree_size(binary_tree *bt, FILE *compressed) {
  unsigned char byte = fgetc(compressed);

  for (int i = 15; i >= 13; i--) {
    if (is_bit_i_set(byte, i % 8)) {
      trash_size += powow(2, i);
    }
  }

  for (int i = 12; i >= 0; i--) {
    if (is_bit_i_set(byte, i % 8)) {
      tree_size += powow(2, i);
    }
    if (i == 8) {
      byte = fgetc(compressed);
    }
  }
}

void print_file(binary_tree *bt, FILE *compressed, FILE *extracted) {
  int pos_byte = -1;
  unsigned char c;
  int x;
  binary_tree *aux_bt = bt;
  while(1) {
    if(pos_byte < 0) {
      pos_byte = 7;
      x = fgetc(compressed);
      c = x;
      if(x == EOF) {
        break;
      }
    }
    if(aux_bt->left == NULL && aux_bt->right == NULL) {
      fputc(aux_bt->item, extracted);
      aux_bt = bt;
    } else {
      if(!is_bit_i_set(c, pos_byte)) {
        aux_bt = aux_bt->left;
        pos_byte--;
      } else {
        aux_bt = aux_bt->right;
        pos_byte--;
      }
    }
  }
}

void extract(binary_tree *bt, FILE *compressed, FILE *extracted) {
  calc_tree_size(bt, compressed);

  bt = create_tree(bt, compressed, '0');

  //print_pre_order(bt);

  print_file(bt, compressed, extracted);
}

int main() {
  binary_tree *bt = create_empty_binary_tree();
  FILE *compressed = fopen("compress_file.huff", "r");
  FILE *extracted = fopen("jubileu.txt", "w+");

  if (compressed == NULL || extracted == NULL) {
    puts("File error");
    return 0;
  }
  
  extract(bt, compressed, extracted);
  
  fclose(compressed);
  fclose(extracted);
  // print_pre_order(bt);
}
