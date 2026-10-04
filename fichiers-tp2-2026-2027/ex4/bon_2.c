
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bon_2.h"

int search_pattern_bon_2(char *pattern, char *message) {
    int messlength = strlen(message);
    int patlength = strlen(pattern);
    int i, j;

    for (i=0; i<(messlength-patlength+1); i++) {

        for (j=0; j<patlength; j++)  {
            if (message[i+j] != pattern[j]) break;
        }
        if (j == patlength) return(i);
    }
    return(-1);
}
