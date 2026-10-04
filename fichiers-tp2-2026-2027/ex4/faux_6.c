#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "faux_6.h"

int search_pattern_faux_6(char *pattern, char *message) {
  if (pattern==NULL || message==NULL)
    return -1;

  int n= strlen(pattern);
  int m= strlen(message);

  if (n>m)
    return -1;
  
  for (int i=0; i<m; i++){
    if(pattern[0]==message[i]){
      for(int j=0; j<n; j++){
        if (j==n-1) return i;
        if (pattern[j]!=message[i+j] && j!=n) break;
        }
    }
  }
  return -1;
}
