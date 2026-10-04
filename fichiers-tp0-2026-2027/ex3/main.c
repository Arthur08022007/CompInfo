#include <stdio.h>
#include <string.h>
#include "ex3.h"

static void print_tab(int *t, int length);

static void print_tab(int *t, int length) {
    if (!t) return;
    for (int i=0; i<length; i++) printf("%d", t[i]);
    printf("\n");
    return;
}

int main(void)
{
    int test[10] = {1,0,0,1,1,0,0,0,1,0};
    printf("The array:\n");
    print_tab(test, 10);
    binary_order(test, 10);
    printf("The sorted array: \n");
    print_tab(test, 10);

    return (0);
}
