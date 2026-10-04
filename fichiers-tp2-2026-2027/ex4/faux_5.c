#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "faux_5.h"

int search_pattern_faux_5(char *pattern, char *message) {

  if (pattern==NULL || message==NULL)
    return -1;

  int pattern_size = strlen(pattern);
  int message_size = strlen(message);

  if (pattern_size>message_size)
    return -1;
  
  int i=0;
  int j=0;
  int position;

  if(pattern_size>message_size){
    printf("Impossible de trouver le pattern dans le message.\n");
    return 0;
  }

  while (j<pattern_size && i<message_size){
    if(message[i]==pattern[j]){  /* Si l'élément i du message est égale à l'élément j du pattern, on avance d'une case dans le pattern.*/
      j++;
    }
    
    else{
      j=0;
    
      if(message[i]==pattern[j]){ /* Je prends en compte le cas où le pattern se trouverait juste après un passage qui contiendrait le début du pattern*/
        j=1;
      }
    }
     i++;
  }
  if(j==pattern_size){
    position= i - pattern_size; /* Je retrouve la position du début en retirant la taille du pattern à l'indice i qui vaut la position de la dernière lettre+1*/
  }
  if(i== message_size && j!= pattern_size){ /*Si on est arrivé à la fin du message et que le pattern n'a pas été retrouvé*/
    return -1;
  }
 return position;
}
