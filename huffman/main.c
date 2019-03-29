/*
 * main.c
 *
 *  Created on: 26 de mar de 2019
 *      Author: alef farias, joao paulo, milena nunes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_compress.h"
#include "_extract.h"

int main() {
  int option;

  puts("HUFFMAN");
  getchar();

  while (1) {
    puts("Digite:\n0 para compressao\n1 para descompressao\n2 para sair\n");

    scanf("%d", &option);

    while (option != 0 && option != 1 && option != 2) {
      puts("Digite corretamente!");
      scanf("%d", &option);
    }

    if (option == 2) {
      break;
    }

    puts("Nao vai durar nem uma hora!\n.\n.\n.");

    (option) ? decompress() : compress();

    getchar();
  }

  return 0;
}
