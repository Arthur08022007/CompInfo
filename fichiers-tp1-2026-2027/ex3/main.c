#include <stdio.h>
#include <string.h>
#include "power.h"

/* Driver program to test above functions */
int main()
{

  printf("%f^%d = %f\n", 2.0, 10, pow_iter2(2.0, 10));
  printf("%f^%d = %f\n", -3.0, 5, pow_iter2(-3.0, 5));
  printf("%f^%d = %f\n", 2.0, 10, pow_rec3(2.0, 10));
  printf("%f^%d = %f\n", -3.0, 5, pow_rec3(-3.0, 5));

  return (0);
}
