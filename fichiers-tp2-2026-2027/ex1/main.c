#include <stdio.h>
#include <string.h>
#include "filter.h"


int pair(int n){
  return n%2;
}

/* Driver program to test above functions */
int main(void) 
{ 
  int myarray[] = {1, 2, 3, 4, 6, 7, 9, 10}; // Tableau final [1,3,7,9]

  int finalLenght=filter(pair, myarray, 8);

  /*printf("La longueur finale est %d \n",finalLenght);
  for (int i=0;i<finalLenght;i++){
    printf("%d ",myarray[i]);
  }
  printf("\n");*/
  
  return 0; 
} 

