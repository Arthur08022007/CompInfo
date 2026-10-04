#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ex2.h"

int inversions(int tab[], int length) {
    int count=0;
    for (int i=0; i<length; i++){
        for (int j=i+1; j<length; j++){
            if (tab[i]>tab[j]){
                count++;
            }
        }
    }

    return count;
}
