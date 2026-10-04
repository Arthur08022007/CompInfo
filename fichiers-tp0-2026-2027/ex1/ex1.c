#include <stdio.h>
#include <math.h>
#include "ex1.h"
#include <stdbool.h>

int check_unique(int tab[], int length) {
    for (int i=0; i<length; i++){
        for (int j=i+1; j<length; j++){
            if (tab[i]==tab[j]){
                printf("%d, %d",i,j);
                return 0;
            }
        }
    }
    return 1;
}
