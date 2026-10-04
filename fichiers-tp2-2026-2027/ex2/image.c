#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "image.h"

int **load_image(char *file, int *length)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file '%s'.\n", file);
        exit(EXIT_FAILURE);
    }

    // Magic number
    char magic[3];
    magic[2] = '\0';
    if (fscanf(fp, "%2c", magic) < 1)
    {
        fprintf(stderr, "Error '%s'.\n", magic);
        exit(EXIT_FAILURE);
    }

    if (strncmp(magic, "P2", 2) != 0)
    {
        fprintf(stderr, "ERROR.\n");
        exit(EXIT_FAILURE);
    }

    // Image dimensions
    int w, h;
    if (fscanf(fp, "%d %d", &w, &h) < 2)
    {
        fprintf(stderr, "Error '%d' '%d'.\n", w, h);
        exit(EXIT_FAILURE);
    }

    if (w != h)
    {
        fprintf(stderr, "Error while loading image: width and height should be the same,"
                        " got: %d and %d.\n",
                w, h);
        exit(EXIT_FAILURE);
    }

    // Max pixel value
    int px;
    if (fscanf(fp, "%d", &px) < 1)
    {
        fprintf(stderr, "Error.\n");
        exit(EXIT_FAILURE);
    }

    if (px != 255)
    {
        fprintf(stderr, "Error while loading image, expected max pixel value to be 255,"
                        " got %d.\n",
                px);
        exit(EXIT_FAILURE);
    }

    // Load array
    int **array = (int **)malloc(w * sizeof(int *));
    for (int i = 0; i < w; i++)
    {
        array[i] = (int *)malloc(w * sizeof(int));
    }

    for (int r = 0; r < w; r++)
    {
        for (int c = 0; c < w; c++)
        {
            if (fscanf(fp, "%d", &array[r][c]) < 1)
            {
                fprintf(stderr, "Error.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(fp);

    // Set length
    *length = w;

    return array;
}

void save_image(char *file, int length, int **array)
{
    FILE *fp = fopen(file, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file '%s'.\n", file);
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "P2\n");

    fprintf(fp, "%d %d\n", length, length);

    fprintf(fp, "255\n");

    for (int r = 0; r < length; r++)
    {
        for (int c = 0; c < length; c++)
        {
            fprintf(fp, "%d ", array[r][c]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}

void free_image(int length, int **array)
{
    for (int i = 0; i < length; i++)
    {
        free(array[i]);
    }

    free(array);
}
