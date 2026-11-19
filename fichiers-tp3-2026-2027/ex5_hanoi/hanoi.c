#include <stdio.h>
#include <stdlib.h>
#include "stack-int.h"

// Prototypes

void show_towers(Stack *s1, Stack *s2, Stack *s3);
void hanoi_iter(int n);

/* Affiche le contenu des trois piles représentant les tours
 * (le bas de la pile est à gauche)
 */

void show_towers(Stack *s1, Stack *s2, Stack *s3) {
  printf("  Tower 1:");
  stackPrint(s1);
  printf("\n  Tower 2:");
  stackPrint(s2);
  printf("\n  Tower 3:");
  stackPrint(s3);
  printf("\n");  
}

/* Résolution itérative du problème des tours de Hanoï */

void hanoi_iter(int n) {
  Stack *s1 = stackCreate();
  Stack *s2 = stackCreate();
  Stack *s3 = stackCreate();

  // Remplit la première tour avec tous les disques
  for (int i = n; i > 0 ; i--)
    stackPush(s1, i);

  printf("Initial state\n");
  show_towers(s1, s2, s3);
  
  int nbmoves = 0;
  
  do {
    
    Stack *stmp1, *stmp2;

    // Mouvement 1:
    // ------------
    // Rechercher la pile contenant le disque 1 à son sommet et ensuite
    // déplacer le disque vers la pile de droite
    // Truc: pour faciliter l'implémentation de la seconde étape, on fera
    // pointer stmp1 et stmp2 vers les deux piles qui ne contiennent pas
    // le disque 1 après cette opération.
    
    // A compléter
    // ...

    printf("Move %d:\n", ++nbmoves);
    show_towers(s1, s2, s3);

    // Vérifie si on n'a pas déjà déplacé toute la pile
    if (stackIsEmpty(s1) && (stackIsEmpty(s2) || stackIsEmpty(s3)))
      break;

    // Mouvement 2:
    // ------------
    // Trouver le plus petit disque entre celui au sommet de stmp1 et celui
    // au sommet de stmp2 et le déplacer vers l'autre pile. Si une des deux piles
    // est vide, on déplace celui au sommet de l'autre vers cette pile.
    

    // A compléter
    // ...

    printf("Move %d:\n", ++nbmoves);
    show_towers(s1, s2, s3);
    
  } while (!(stackIsEmpty(s1) && (stackIsEmpty(s2) || stackIsEmpty(s3))));
  
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Give the number of disks as (the single) argument\n");
    exit(-1);
  }
  
  int n = atoi(argv[1]);
  
  hanoi_iter(n);
  
  return 0;  

}
