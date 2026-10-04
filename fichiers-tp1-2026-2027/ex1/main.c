#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maxsum.h"

int main()
{
  int tab[8] = {-4,2,4,-5,6,-7,0,1};
  int length = 8;
  
  printf("max_sum_naive: The maximum sum is %d (should be 7)\n", max_sum_naive(tab, length));
  printf("max_sum_opt: The maximum sum is %d (should be 7)\n", max_sum_opt(tab, length));
  
  return (0);
}
