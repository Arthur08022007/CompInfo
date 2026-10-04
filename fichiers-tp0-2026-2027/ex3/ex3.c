#include "ex3.h"

static void swap(int tab[], int i, int j);

static void swap(int tab[], int i, int j) {
  int tmp = tab[i];
  tab[i] = tab[j];
  tab[j] = tmp;
}

void binary_order(int tab[], int length) {
  int left = 0;
  int right = length - 1;

  while (left < right) {
    while (left < right && tab[left] == 0) {
      left++;
    }
    while (left < right && tab[right] == 1) {
      right--;
    }
    if (left < right) {
      swap(tab, left, right);
      left++;
      right--;
    }
  }
}
