#include <stdio.h>
#include <stdlib.h>


int main () {
	int caracter = 0;
  	int array[256];
	FILE *arquivo = fopen("test.txt", "r");
	if (arquivo == NULL) {
		printf("File error\n");
		return 0;
	}

	for(int j = 0; j < 256; j++) {
		array[j] = 0;
	}

  	while(caracter != EOF) {
  		caracter = fgetc(arquivo);
  		array[caracter]++;

  	}

  	for(int j = 0; j < 256; j++) {
  		printf("%c %d\n", j, array[j]);
  	}

  	//fclose(arquivo);
	return 0;
}