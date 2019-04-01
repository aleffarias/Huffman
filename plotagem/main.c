#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"
#include "binary_search_tree.h"

int main () {
  int i, lim, chosen, cost;
  
  node *list = create_linked_list();
  binary_tree *bt = create_empty_binary_tree();

  FILE *output_list = fopen("list.txt", "w+");
  FILE *output_tree = fopen("tree.txt", "w+");

  puts("LISTA ENCADEADA vs ARVORE DE BUSCA BINARIA");
  puts("Digite a quantidade de numeros");
  scanf("%d", &lim);
  printf("Intervalo: [0,%d]\n", lim);

  srand(time(NULL));

  int numbers[lim+1];
  
  for (i = 0; i <= lim+1; i++) {
    numbers[i] = 0;
  }

  for(i = 1; i <= lim; i++) { 
      
    do {
      chosen = rand() % lim; 
    } while (numbers[chosen]);
    printf("%d\n", chosen);
    numbers[chosen] = 1;
    
    list = add_list(list, chosen);
    bt = add_tree(bt, chosen);
  }

  for(i = 0; i < lim; i++) { 
    cost = search_list(list, i);
    fprintf(output_list ,"%d\t%d\n", i, cost);
    cost = search_tree(bt, i);
    fprintf(output_tree, "%d\t%d\n", i, cost);
  }

  fclose(output_list);
  fclose(output_tree);

  return 0;
}
