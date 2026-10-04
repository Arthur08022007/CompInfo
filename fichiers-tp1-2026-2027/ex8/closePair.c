#include <stdlib.h>
#include <stdio.h>

int *closest_pair(int tab[], int n);
void generate_rand_data(int length, int tab[length], int m);

void generate_rand_data(int length, int tab[length], int m) {
  for (int i = 0; i < length; i++)
     tab[i] = rand() % (2*m) - m;
}

int *closest_pair(int tab[], int n) {
  // Votre code ici
}


int main() {
  // Votre code ici pour le test
}
