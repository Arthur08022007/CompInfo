#include "findfirsttrue.h"
#include <stdio.h>
#include <stdbool.h>

// findFirstTrue (generic).

int findFirstTrue(bool (*f)(void *, int, void *), void *tab, int length, void *param)
{
    int left = 0;
    int right = length;

    while (left < right) {
        int middle = left + (right - left) / 2;
        if (f(tab, middle, param)) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    return left;
}

// Application 1

static bool isPointOutOfBall(void *tab, int index, void *param)
{
    float radius = ((float *)param)[0];
    Point *points = (Point *)tab;
    float x = points[index].x - points[0].x;
    float y = points[index].y - points[0].y;
    return (x * x + y * y > radius * radius);
}

int findLastPointinBall(Point *tabp, int length, float radius)
{
    float param[1] = {radius};
    int firstOut = findFirstTrue(isPointOutOfBall, tabp, length, param);
    return firstOut - 1;
}

// Application 2

static bool isEnough(void *tab, int index, void *param)
{
    float *p = (float *)param;
    float percentile = p[0];
    int length = (int)p[1];
    int *intTab = (int *)tab;
    return (intTab[index] > percentile* intTab[length - 1]);
}

int getPercentile(int *tab, int length, float p)
{
    float param[2] = {p, (float)length};
    int firstEnough = findFirstTrue(isEnough, tab, length, param);
    return firstEnough;
}
