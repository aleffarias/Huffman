#include <stdio.h>
#include <stdlib.h>

#include "compress.h"
#include "decompress.h"

int main () {
  int option;

  puts ("HUFFMAN");
  getchar ();

  while (1) {
    puts ("Digite:\n0 para compressao\n1 para descompressao\n2 para sair\n");

    scanf ("%d", &option);
    
    while (option != 0 && option != 1 && option != 2) {
      puts ("Digite corretamente!");
      scanf ("%d", &option);
    }

    if (option == 2) {
      break;
    }
    
    (option)? decompress() : compress ();
    
    getchar ();
  }

  return 0;
}
