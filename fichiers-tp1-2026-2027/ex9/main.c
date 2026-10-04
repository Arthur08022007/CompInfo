#include <stdio.h>
#include "bitonic.h"

int main() {
  int t[11] = {1,3,6,7,9,13,14,15,10,5,4};
  printf("Résultat bitonic_maximum: %d (réponse attendue: 7)\n", bitonic_maximum(t, 11));
  printf("Résultat bitonic_search (recherche de 7): %d (réponse attendue: 3)\n", bitonic_search(7,t,11));
  printf("Résultat bitonic_search (recherche de 8): %d (réponse attendue: -1)\n", bitonic_search(8,t,11));
  return 0;
}
