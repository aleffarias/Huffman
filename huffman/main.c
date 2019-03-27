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



int main() {
	int key;
	while(1) {
		printf("Para comprimir, digite 1, para extrair, digite 2, para encerrar o programa, digite -1");
		scanf("%d", &key);
		if(key == 1) {
			priority_queue *pq = create_priority_queue();
			hash_table *ht = create_hash_table();

			FILE *file = fopen("huffman.txt", "r");
			FILE *compressed = fopen("compress_file.huff", "w+");

			if (file == NULL || compressed == NULL) {
			  puts("File error");
			  return 0;
			}

			compress(ht, pq, file, compressed);

			fclose(file);

			fclose(compressed);
		} else if(key == 2) {

		} else {
			return 0;
		}
	}
  return 0;
}
