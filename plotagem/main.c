#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linked_list.h"
#include "binary_search_tree.h"

void swap (int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

void quick_sort (int *v, int size) {
  if (size <= 1) {
    return;
  } else {
    int aux, pivot = v[size/2], a = 0, b = size - 1;
    while (a < b) {
      while (v[a] < pivot) a++;
      while (v[b] > pivot) b--;
      if (a < b) {
        swap (&v[a], &v[b]);
        if (v[a] == v[b]) a++;
      }
    }
    quick_sort (v, b);
    quick_sort (v+a, size-a);
  }
}

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

  int numbers[lim+1], sort_list[lim], sort_tree[lim];
  
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
    sort_list[i] = cost_list;
    sort_tree[i] = cost_tree;
  }

  quick_sort (sort_list, lim);
  quick_sort (sort_tree, lim);

  for(i = 0; i < lim; i++) { 
    fprintf(output, "%d\t%d\t%d\n", i+1, sort_list[i], sort_tree[i]);  
  }

  fclose(output);

  return 0;
}
