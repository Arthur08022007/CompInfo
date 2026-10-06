#include <stdio.h>
#include "sort.h"

void swap_int(void *array, int i, int j);
int compare_int(void *array, int i, int j);

void swap_int(void *array, int i, int j) {
  int temp = ((int*)array)[i];
  ((int*)array)[i] = ((int*)array)[j];
  ((int*)array)[j] = temp;
}

int compare_int(void *array, int i, int j) {
  return (((int*)array)[i] <= ((int*)array)[j]);
}

int main() {
  
  int A[5]={5, 2, 3, 1, 4};

  printf("Avant le tri:");
  for (int i=0; i<5; i++)
    printf(" %d",A[i]);
  printf("\n");
  
  sort(A, 5, compare_int, swap_int);

  printf("Après le tri:");
  for (int i=0; i<5; i++)
    printf(" %d",A[i]);
  printf("\n");

  return 0;
}
