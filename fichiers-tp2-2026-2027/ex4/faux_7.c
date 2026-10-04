#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "faux_7.h"

int search_pattern_faux_7(char *pattern, char *message) {
  if (pattern==NULL || message==NULL)
    return -1;

  int messlength=strlen(message);
  int pattlength=strlen(pattern);

  if (messlength<pattlength)
    return -1;
  
  int i=0;
  for(;i<messlength;i++){

    if (message[i]==pattern[0]){
       int y=1;
         for(;message[i+y]==pattern[y] && (i+y)<messlength;y++){
            if (y==pattlength-1)
                return i;
         }     
    }  
  }
   
    return -1;
}
