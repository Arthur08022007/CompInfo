#include <stdio.h>
#include <string.h>
#include "determinant.h"

/* Driver program to test above functions */
int main() 
{ 

  double mat33[3][3] = {{1, 0, 1},
			{-1, 3, 6},
			{0, 8, 1}};
  
  double mat55[5][5] = {{3.4, 3.5, 2.8, 0.7, 1.2},
			{1.9, 8.3, 7.5, 0.5, 5.6},
			{2.5, 5.8, 7.5, 5.3, 4.6},
			{6.1, 5.4, 3.8, 7.7, 0.1},
			{4.7, 9.1, 5.6, 9.3, 3.3}};

  printf("Determinant of 3x3 matrix is %f (should be -53.0)\n", determinant(3, mat33));
  printf("Determinant of 5x5 matrix is %f (should be 568.938440)\n", determinant(5, mat55));

  return 0;

} 

