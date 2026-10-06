#include <stdio.h>
#include "complex.h"
#include "sort.h"

void swap_complex(void *array, int i, int j);
int compare_complex_mod(void *array, int i, int j);

void swap_complex(void *array, int i, int j) {
  complex temp = ((complex*)array)[i];
  ((complex*)array)[i] = ((complex*)array)[j];
  ((complex*)array)[j] = temp;
}

int compare_complex_mod(void *array, int i, int j) {
  return (complex_modulus(((complex*)array)[i]) <= complex_modulus(((complex*)array)[j]));
}

int main() {
  
  complex C[5]={{2,5}, {3,4}, {0,3}, {1,2}, {1,0}};

  printf("Avant le tri:\n");
  for (int i=0; i<5; i++)
    printf("%i - (%f,%f) -> mod = %f\n", i, C[i].re, C[i].im, complex_modulus(C[i]));
  printf("\n");
  
  sort(C, 5, compare_complex_mod, swap_complex);

  printf("Après le tri:\n");
  for (int i=0; i<5; i++)
    printf("%i - (%f,%f) -> mod = %f\n", i, C[i].re, C[i].im, complex_modulus(C[i]));
  printf("\n");
  
  return 0;
}
