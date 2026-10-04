#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maxsum.h"

const int NBTRIALS = 1;

void generate_rand_data(int length, int tab[length], int m);


void generate_rand_data(int length, int tab[length], int m) {
  for (int i = 0; i < length; i++)
     tab[i] = rand() % (2*m) - m;
}

int main(int argc, char **argv) {

  int n = 32000;
  
  int tab[n];

  srand(time(NULL));

  // votre code ici
  
  exit(0);
  
}
