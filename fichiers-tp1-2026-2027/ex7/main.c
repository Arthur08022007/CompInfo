#include <stdio.h>
#include <string.h>
#include "kendalltau.h"

#define SIZE 10

int main(void)
{
    double x[SIZE] = {8.0, 10.0, 4.0, 5.0, 3.0, 12.0, 2.0, 1.0, 6.0, 9.0};
    double y[SIZE] = {2.0, 10.0, 3.0, 5.0, 4.0, 12.0, 8.0, 1.0, 6.0, 9.0};

    printf("Vector x = [");
    for (int i = 0; i < SIZE; i++)
    {
        printf(" %f", x[i]);
    }
    printf("]\n");
    printf("Vector y = [");
    for (int i = 0; i < SIZE; i++)
    {
        printf(" %f", y[i]);
    }
    printf("]\n");

    printf("Kendall's Tau Coefficient = %f (expected %f)\n", kendallTauFast(x, y, SIZE), kendallTauSlow(x, y, SIZE));


    return (0);
}
