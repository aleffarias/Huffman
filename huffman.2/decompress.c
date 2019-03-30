#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"


int TRASH_SIZE = 0;
int TREE_SIZE = 0;


int is_bit_i_set(unsigned char c, int i) {
  unsigned char mask = 1 << i;
  return mask & c;
}

void write_file(binary_tree *bt, FILE *compressed, FILE *extracted, unsigned long long int file_size) {
  int byte, pos_byte = -1;
  unsigned char c;
  binary_tree *aux_bt = bt;

  while (1) {
    if (pos_byte < 0) {
      byte = fgetc(compressed);
      c = byte;
      pos_byte = 7;
    }

    if (aux_bt->left == NULL && aux_bt->right == NULL) {
      fputc(aux_bt->item, extracted);
      aux_bt = bt;
      if ((ftell (compressed) == file_size) && (pos_byte == TREE_SIZE-1)) {
        return;
      }
    } else {
      (is_bit_i_set(c, pos_byte))? (aux_bt = aux_bt->right) : (aux_bt = aux_bt->left);
      pos_byte--;
    }
  }
}

binary_tree *create_tree(binary_tree *bt, FILE *compressed, unsigned char byte) {
  if (TRASH_SIZE != 0) {
    byte = fgetc(compressed);
    TRASH_SIZE--;

    if (byte == '*') {
      bt = create_binary_tree(byte, NULL, NULL);
      bt->left = create_tree(bt->left, compressed, byte);
      bt->right = create_tree(bt->right, compressed, byte);
    } else {
      if (byte == '\\') {
        byte = fgetc(compressed);
        TRASH_SIZE--;
      }
      bt = create_binary_tree(byte, NULL, NULL);
    }
    return bt;
  }
  return bt;
}

int power(int a, int b) {
  int base = a;
  if (!b) {
    return 1;
  }
  for (int i = 1; i < b; i++) {
    a *= base;
  }
  return a;
}

void calc_tree_size(binary_tree *bt, FILE *compressed) {
  unsigned char byte = fgetc(compressed);

  for (int i = 15; i >= 13; i--) {
    if (is_bit_i_set(byte, i % 8)) {
      TREE_SIZE += power(2, i%13);
    }
  }

  for (int i = 12; i >= 0; i--) {
    if (is_bit_i_set(byte, i % 8)) {
      TRASH_SIZE += power(2, i);
    }
    if (i == 8) {
      byte = fgetc(compressed);
    }
  }
}

void decompress () {
  binary_tree *bt = create_empty_binary_tree();
  char my_file_comp[50], my_file_ext[50];

  puts ("Qual arquivo deseja extrair?\nInsira: arquivo.extensao");
  scanf ("%s", my_file_comp);
  FILE *compressed = fopen(my_file_comp, "r");

  if (compressed == NULL) {
    puts("File error\n");
    return;
  }

  fseek (compressed, 0, SEEK_END);
  unsigned long long int file_size = ftell (compressed);
  rewind (compressed);

  puts ("\nNomeie o arquivo de saída\nInsira: arquivo.extensao");
  scanf ("%s", my_file_ext);
  FILE *extracted = fopen(my_file_ext, "w+");
  puts ("\nNao vai durar nem uma hora!\n.\n.\n.");

  calc_tree_size(bt, compressed);

  bt = create_tree(bt, compressed, '0');

  write_file(bt, compressed, extracted, file_size);

  fclose(compressed);
  fclose(extracted);
  
  //print_pre_order(bt);
  puts ("Concluido!\n");
}
