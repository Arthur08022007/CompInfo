#ifndef _IMAGE_H
#define _IMAGE_H

int **load_image(char *file, int *length);
void save_image(char *file, int length, int **array);
void free_image(int length, int **array);

#endif
