#include <stdio.h>
#include <string.h>
#include "permute.h"

/* Driver program to test above functions */
int main() 
{ 
    char str[] = "ABC"; 
    int n = strlen(str); 
    permute(str, n); 
    return 0; 
} 

