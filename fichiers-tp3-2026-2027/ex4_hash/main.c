#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "set.h"

#define N 100000
#define L 6

// génère un tableau contenant nbstrings chaînes de longueur lengthstring construites sur
// les lettres présentent dans la chaîne alphabet de taille sizealphabet.

char **generate_random_string_array(int nbstrings, int lengthstring, char *alphabet, int sizealphabet);

// Libère la mémoire prise par le tableau array de taille n

void freeArray(char **array, int n);

// affiche l'intersection entre les deux tableaux (à implémenter).

void printIntersection(char **tab1, int n1, char **tab2, int n2); 

char **generate_random_string_array(int nbstrings, int lengthstring, char *alphabet, int sizealphabet) {

  char **array = malloc(nbstrings*sizeof(char *));

  for (int i = 0; i < nbstrings; i++) {
    array[i] = malloc((lengthstring+1) * sizeof(char));
    int j = 0;
    for (j = 0; j < lengthstring; j++) {
      array[i][j] = alphabet[rand() % sizealphabet];
    }
    array[i][j] = '\0';
  }
  return array;
}

void freeArray(char **array, int n) {
  for (int i = 0; i < n; i++) {
    free(array[i]);
  }
  free(array);
}


// A completer
void printIntersection(char **tab1, int n1, char **tab2, int n2) {

  // ...
  printf("La fonction printIntersection doit etre completee\n");
  
}

int main(void) {

  srand(time(NULL));

  char **tab1 = generate_random_string_array(N, L, "abcdefghijklmnopqrstuvwxyz", 26);
  char **tab2 = generate_random_string_array(N, L, "abcdefghijklmnopqrstuvwxyz", 26);

  printIntersection(tab1, N, tab2, N);

  freeArray(tab1, N);
  freeArray(tab2, N);

  exit(0);
}
