#include "findfirsttrue.h"
#include <stdio.h>
#include <stdbool.h>

// findFirstTrue (generic).

int findFirstTrue(bool (*f)(void *, int, int, void *param), void *tab, int length, void *param)
{
    int left = 0;
    int right = length;

    while (left < right) {
        int middle = left + (right - left) / 2;
        if (f(tab, middle, length, param)) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    return left;
}

// Application 1


static bool isPointOutOfBall(void *tab, int index, int length, void *param)
{
    (void)length;
    float radius = ((float *)param)[0]; 
    Point *points = (Point *)tab;
    float x = points[index].x;
    float y = points[index].y;
    return (x*x + y*y > radius*radius);
}

int findLastPointinBall(Point *tabp, int length, float radius)
{
    float param[1] = {radius};
    int firstOut = findFirstTrue(isPointOutOfBall, tabp, length, param);
    return firstOut - 1;
}


// Application 2

bool isEnough(void *tab, int index,int length, void *param){
    float p=((float *)param)[0];
    int *intTab=(int *)tab;
    return (intTab[index]>p*intTab[length-1]);
    
}



int getPercentile(int *tab, int length, float p)
{
    float param[1]={p};
    int firstEnough=findFirstTrue(isEnough, tab, length, param);
    return firstEnough;
}
