#include <stdlib.h>
#include <stdio.h>

int identity(int tab[], int n);

int identity(int tab[], int n) {

  // Votre code ici

}

int main() {

  int tab1[8] = {-3,-1,1,2,4,6,10,15};
  int tab2[10] = {-15,-10,-5,-4,1,3,10,15,20,25};

  printf("Votre résultat sur tab1: %d (résultat attendu: 4)\n", identity(tab1,8));
  printf("Votre résultat sur tab2: %d (résultat attendu: -1)\n", identity(tab2,10));

  exit(0);
}
