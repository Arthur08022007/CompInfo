#include <stdio.h>
#include <string.h>
#include "argmin.h"

void print_t(int t[], int l);

/* Driver program to test above functions */
int main()
{
    int t[10] = {13,6,53,4,4,7,8,9,5,10};
    print_t(t, 10);
    printf("Argmin of the array : %d\n", argmin(t, 10));
    return (0);
}

void print_t(int t[], int l) {
    int i;
    for (i=0; i<l; i++) {
        printf("%d ", t[i]);
    }   
    printf("\n");
    return;
}
