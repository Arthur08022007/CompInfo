
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "faux_2.h"

int search_pattern_faux_2(char *pattern, char *message) {
  if (pattern==NULL || message==NULL)
    return -1;
    
    int messlength = strlen(message);
    int patlength = strlen(pattern);

    if (messlength<patlength)
      return -1;

    int i;
    int j;
    // parcourt du message
    for (i=0; i< (messlength - patlength) ; i++) {
        int cmp = 1; //compteur de lettres identiques
        //parcourt du pattern en parallèle avec le message
        for (j=0; j<patlength; j++) {
            if (message[i+j] == pattern[j]) {
                cmp = cmp +1;
                // on continue la boucle
            if (cmp == patlength) {
                    return i;
                }
            } else {
                break;
            }
           
            
        }
        }
  return -1;
}
