#include <stdio.h>
#include <string.h>
#include "ex2.h"

int main(void)
{
    int t[10] = {8,10,4,5,3,12,7,3,5,10};
    printf("Tabular is [");
    for (int i=0; i<10; i++){
        if (i<9)
            printf("%d,",t[i]);
        else
            printf("%d",t[i]);
    }
    printf("]\n");
    printf("Number of inversions: %d (should be 22)\n", inversions(t,10));
    return (0);
}
