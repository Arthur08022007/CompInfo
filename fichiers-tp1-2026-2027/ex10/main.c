#include <stdio.h>
#include <stdlib.h>

#include "searchmatrix.h"

#define LENGTH 4

int main(void)
{
  int tab[LENGTH][LENGTH] = {
      {1, 2, 3, 15},
      {10, 11, 20, 21},
      {11, 12, 30, 35},
      {13, 24, 31, 40}};

  printf("2D Array:\n");
  for (int i = 0; i < LENGTH; i++)
  {
    for (int j = 0; j < LENGTH; j++)
      printf("%2d ", tab[i][j]);

    printf("\n");
  }
  printf("\n");

  int values[3] = {30, 17, 10};
  for (int i = 0; i < 3; i++)
  {
    if (search_matrix(LENGTH, tab, values[i]))
      printf("%d is in the array.\n", values[i]);

    else
      printf("%d is not in the array.\n", values[i]);
  }
}
