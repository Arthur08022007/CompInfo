#include <stdio.h>

#include "intervals.h"

int main()
{
  const int length = 4;
  float tab[][2] = {{2.0, 4.5}, {1.0, 3.0}, {7.0, 8.0}, {6.0, 9.0}};

  printf("Array of intervals:\n");
  for (int i = 0; i < length; i++)
  {
    printf("[%.2f,%.2f]", tab[i][0], tab[i][1]);
  }
  printf("\n\n");

  float res = compute_length(tab, length);

  printf("Length of the union: %.2f\n", res);
}
