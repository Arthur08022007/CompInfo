#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "findfirsttrue.h"
#include "image.h"

void print_point_array(Point *parray, int length);

void print_point_array(Point *parray, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf(" (%f,%f)", parray[i].x, parray[i].y);
  }
  printf("\n");
}

#define INPUTIMAGE "airplane.pgm"
#define OUTPUTIMAGE "binarized_airplane.pgm"
#define PERC 0.5

int main(void)
{
  printf("Testing findLastPointInBall.\n");

  Point parray[6] = {{8.0, 8.0}, {0.5, 0.5}, {10.0, 10.0}, {20.0, 20.0}, {40.0, 40.0}, {120.0, 120.0}};
  float radius = 20.0;

  printf("Array: ");
  print_point_array(parray, 6);
  printf("Radius: %f\n", radius);
  int i = findLastPointinBall(parray, 6, radius);
  printf("Last point in ball is point %d ((%f,%f)).\n", i, parray[i].x, parray[i].y);

  printf("\nTesting getPercentile for the binarization of the image in file %s.\n", INPUTIMAGE);

  int length;
  int **array = load_image(INPUTIMAGE, &length);

  int cumhistogram[256];

  for (int i = 0; i < 256; i++)
    cumhistogram[i] = 0;

  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length; j++)
    {
      cumhistogram[array[i][j]]++;
    }
  }

  for (int i = 1; i < 256; i++)
    cumhistogram[i] += cumhistogram[i - 1];

  int pos = getPercentile(cumhistogram, 256, PERC);

  printf("Threshold value is %d (percentile %f).\n", pos, PERC);

  for (int i = 0; i < length; i++)
  {
    for (int j = 0; j < length; j++)
    {
      if (array[i][j] < pos)
        array[i][j] = 0;
      else
        array[i][j] = 255;
    }
  }

  save_image(OUTPUTIMAGE, length, array);

  printf("The binarized image is in the file %s.\n", OUTPUTIMAGE);

  free_image(length, array);

  return EXIT_SUCCESS;
}
