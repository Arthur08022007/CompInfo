#include <stdio.h>
#include <string.h>
#include "ex1.h"

int main(void)
{
    int t[10] = {3,10,2,14,3,12,7,4,5,9};
    printf("Tabular is [");
    for (int i=0; i<10; i++){
        if (i<9)
            printf("%d,",t[i]);
        else
            printf("%d",t[i]);
    }
    printf("]\n");
    if (check_unique(t, 10)) {
        printf("All elements are unique.\n");
    } else {
        printf("Elements are not all unique.\n");
    }
    return (0);
}
