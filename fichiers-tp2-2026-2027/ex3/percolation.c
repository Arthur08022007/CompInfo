#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define P 0.5

typedef struct grid_t {
  int **array;
  int size;  
} Grid;

int rand_bit(double p);
Grid *generate_random_grid(int n, float p);
int percolate(Grid *grid);
void flow(Grid *grid);
void flowrec(Grid *grid, int i, int j);
void print_grid(Grid *grid);
  
int main() {

  srand(time(NULL));
  
  // création d'une grille aléatoire
  
  Grid *grid = generate_random_grid(N,P);

  // test de percolation de la grille
  
  printf("Percolate ? ");
  if (percolate(grid))
    printf("Yes\n");
  else
    printf("No\n");

  // affichage de la grille avec les cases marquées
  print_grid(grid);
  
  return 0;
}

int rand_bit(double p){
    if(p == 1.0){
        return 1;   
    }
    double r = ((double)rand())/((double)RAND_MAX);
    return r<p?1:0;
}

Grid *generate_random_grid(int n, float p) {

  Grid *grid = malloc(sizeof(Grid));

  if (grid == NULL)  {
    printf("Erreur d'allocation dans la fonction generate_random_grid\n");
    exit(-1);
  }

  grid->array = malloc(n * sizeof(int *));

  if (grid->array == NULL) {
    printf("Erreur d'allocation dans la fonction generate_random_grid\n");
    exit(-1);
  }

  grid->size = n;
  
  for (int i = 0; i < n; i++) {
    grid->array[i] = malloc(n * sizeof(int));
    if (grid->array[i] == NULL) {
      printf("Erreur d'allocation dans la fonction generate_random_grid\n");
      exit(-1);
    }
    for (int j = 0; j < n; j++) {
      grid->array[i][j] = rand_bit(p);
    }
  }

  return grid;
}

int percolate(Grid *grid) {
  flow(grid);
  int n = grid->size;
  for (int j = 0; j < n; j++)
    if (grid->array[n-1][j] == 2)
      return 1;
  return 0;
}

void flow(Grid *grid) {
  int n = grid->size;
  for (int j = 0; j < n; j++)
    flowrec(grid, 0, j);
}

void flowrec(Grid *grid, int i, int j) {
  // Cas de base
  int n = grid->size;
  if (i < 0 || i >= n || j < 0 || j >= n) return;
  if (grid->array[i][j] == 1 || grid->array[i][j] == 2) return;
  // Cas inductif
  grid->array[i][j] = 2;
  flowrec(grid, i+1, j); // Bas
  flowrec(grid, i, j+1); // Droite
  flowrec(grid, i, j-1); // Gauche
  flowrec(grid, i-1, j); // Haut
}

void print_grid(Grid *grid) {
  int n = grid->size;
  for (int i = 0; i < n; i++) {
    printf("|");
    for (int j = 0; j < n; j++) {
      switch(grid->array[i][j]) { 
      case 0: 
	printf(" ");
	break;
      case 1:
	printf("#");
	break;
      case 2:
	printf("o");
      }
    }    
    printf("|\n");
  }

}
