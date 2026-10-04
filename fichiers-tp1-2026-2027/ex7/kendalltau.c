#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "kendalltau.h"

// Implémentation naïve

// Complexité: O(n^2)

// Remplacez les "..." par la complexité de kendallTauSlow en fonction de n. 
// Ne modifiez rien d'autre sur la ligne que les "...".

double kendallTauSlow(double x[], double y[], int n)
{
    int num = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (((x[i] < x[j]) && (y[i] > y[j])) || ((x[i] > x[j]) && (y[i] < y[j]))) {
                num++;
            }
        }
    }

    return 1.0-4.0*num/(n*(n-1));
}

// Implémentation efficace

// Complexité: O(n log n)

// Remplacez les "..." par la complexité de kendallTauFast en fonction de n. 
// Ne modifiez rien d'autre sur la ligne que les "...".

static void merge(double x[], int lo, int mid, int hi, int n, double y[]){ 
    double tmpx[n];
    double tmpy[n];
    int i=lo;
    int j=mid;
    int k=0;
    while (i < mid && j <= hi){
        if (x[i]<x[j]){
            tmpx[k]=x[i];
            tmpy[k]=y[i];
            i++;
        }else{
            tmpx[k]=x[j];
            tmpy[k]=y[j];
            j++;
        }
        k++;
    }
    while (i < mid){
        tmpx[k] = x[i];
        tmpy[k++] = y[i++];
    }

    while (j <= hi){
        tmpx[k] = x[j];
        tmpy[k++] = y[j++];
    }

    for (k = 0; k < n; k++){
        x[lo + k] = tmpx[k];
        y[lo + k] = tmpy[k];
    }

       
}

static void mergesort_aux(double x[], int lo, int hi, double y[]){
    int n= hi-lo+1;
    if (n<=1){
        return;
    }
    int mid= lo+(n+1)/2;
    mergesort_aux(x,lo,mid-1, y);
    mergesort_aux(x,mid,hi, y);
    merge(x,lo,mid,hi,n,y);

}

double kendallTauFast(double x[], double y[], int length)
{
    int lo=0;
    int hi=length-1;
    mergesort_aux(x, lo, hi, y);
    printf("Sorted Vector x = [");
    for (int i = 0; i < length; i++)
    {
        printf(" %f", x[i]);
    }
    printf("]\n");
    printf("Sorted Vector y = [");
    for (int i = 0; i < length; i++)
    {
        printf(" %f", y[i]);
    }
    printf("]\n");
    double n_discordant=0;
    for (int i=0; i<length; i++){
        for (int j=i+1; j<length; j++){
            if (y[i]>y[j]){
                n_discordant++;
            }
        }
    }
    printf("Discord: %f \n",n_discordant);
    double kendall= 1-(4*(n_discordant)/(length*(length-1)));
    return kendall;
}
