#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"
#include "binary_search_tree.h"

int main () {
  int i, lim, chosen, cost_list, cost_tree;
  
  node *list = create_linked_list();
  binary_tree *bt = create_empty_binary_tree();

  FILE *output = fopen("plot.txt", "w+");

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

  fprintf(output, "numero\tcusto_lista\tcusto_árvore\n");

  for(i = 0; i < lim; i++) { 
    cost_list = search_list(list, i);
    cost_tree = search_tree(bt, i);
    fprintf(output, "%d\t%d\t%d\n", i, cost_list, cost_tree);
  }

  fclose(output);

  return 0;
}
