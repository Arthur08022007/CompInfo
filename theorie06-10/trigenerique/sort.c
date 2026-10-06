#include "sort.h"

void sort(void *array, int length, int (*compare)(void*, int, int),
          void (*swap)(void *, int, int)) {
  int i = 1;
  while (i < length) {
    int j = i;
    while (j > 0 && !(compare(array, j-1,j))) {
      swap(array,j-1,j);
      j--;
    }
    i++;
  }
}
