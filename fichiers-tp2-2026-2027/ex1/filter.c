#include "filter.h"


int filter(int (* f)(int), int *array, int length) {
  for (int i=0;i<length;i++){
    if(!f(array[i])){
      for (int j=i+1;j<length;j++){
        array[j-1]=array[j];
      }
      length--;
      i--;
    }
  }
    
  

  return length;
}   


