#ifndef _FINDFIRSTTRUE_H
#define _FINDFIRSTTRUE_H

#include <stdbool.h>

// Voir l'énoncé du TP pour une description de ces fonctions

int findFirstTrue(bool (*f)(void *, int, int, void *param), void *tab, int length, void *param);

typedef struct point_t
{
  float x;
  float y;
} Point;

int findLastPointinBall(Point *tab, int length, float radius);

int getPercentile(int *tab, int length, float p);

bool isPointInBall(void *tab, int index, int length, void *param);
bool isEnough(void *tab, int index, int length, void *param);

#endif
