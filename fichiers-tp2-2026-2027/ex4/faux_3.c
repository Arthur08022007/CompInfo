
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "faux_3.h"

int search_pattern_faux_3(char *pattern, char *message) {
  if (pattern==NULL || message==NULL)
    return -1;

    int i,j;
    int len_message = strlen(message);
    int len_pattern = strlen(pattern);

    if (len_message<len_pattern)
      return -1;

      
 for(int k=0; k<(len_message-len_pattern);k++){
  i=k;
  j=0;
  while(j<len_pattern&&message[i]==pattern[j]){
        i++,j++;
        if(j==len_pattern)
            return k;
  }
 }
 return -1;
  }
