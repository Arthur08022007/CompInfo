#ifndef _FINDFIRSTTRUE_H
#define _FINDFIRSTTRUE_H

#include <stdbool.h>

int findFirstTrue(bool (*f)(void *, int, void *), void *tab, int length, void *param);

typedef struct point_t
{
  float x;
  float y;
} Point;

int findLastPointinBall(Point *tab, int length, float radius);

int getPercentile(int *tab, int length, float p);

bool isEnough(void *tab, int index, void *param);

#endif
