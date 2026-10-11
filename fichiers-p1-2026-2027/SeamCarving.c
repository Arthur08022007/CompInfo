#include <math.h>
#include <stdlib.h>
#include "PNM.h"
#include "SeamCarving.h"

/*
 * Ces fonctions renvoient une réduction de l’image img donnée en argument de k pixels
 * respectivement en largeur et en hauteur en utilisant la procédure décrite dans la
 * section 1. Ces fonctions doivent créer et renvoyer une nouvelle image et ne doivent
 * pas modifier l’image img passée en argument.
 */

static PNMPixel pixelAt(const PNMImage *image, int row, int col)
{
    return image->data[(size_t)row * image->width + (size_t)col];
}

/* Tourne l'image de 90° vers la droite. L'image source n'est pas modifiée. */
static PNMImage *rotate90Clockwise(const PNMImage *src)
{
    PNMImage *dst = createPNM(src->height, src->width);
    if (!dst) {
        return NULL;
    }

    for (size_t row = 0; row < src->height; row++) {
        for (size_t col = 0; col < src->width; col++) {
            size_t newRow = col;
            size_t newCol = src->height - 1 - row;
            dst->data[newRow * dst->width + newCol] =
                src->data[row * src->width + col];
        }
    }

    return dst;
}

/* Tourne l'image de 90° vers la gauche. L'image source n'est pas modifiée. */
static PNMImage *rotate90CounterClockwise(const PNMImage *src)
{
    PNMImage *dst = createPNM(src->height, src->width);
    if (!dst) {
        return NULL;
    }

    for (size_t row = 0; row < src->height; row++) {
        for (size_t col = 0; col < src->width; col++) {
            size_t newRow = src->width - 1 - col;
            size_t newCol = row;
            dst->data[newRow * dst->width + newCol] =
                src->data[row * src->width + col];
        }
    }

    return dst;
}

PNMImage *shrinkImageWidth(PNMImage *image, int k)
{
    if (!image || k < 0) {
        return NULL;
    }

    PNMImage *current = image;
    for (int step = 0; step < k; step++) {
        int *seam = computeMinEnergyVerticalSeam(current, computePixelEnergyGradient);
        if (!seam) {
            if (current != image) {
                freePNM(current);
            }
            return NULL;
        }

        PNMImage *next = cutImageWidth(current, seam);
        free(seam);
        if (!next) {
            if (current != image) {
                freePNM(current);
            }
            return NULL;
        }

        /* L'image de départ doit rester intacte : on ne libère que les
         * intermédiaires créés par les itérations précédentes. */
        if (current != image) {
            freePNM(current);
        }
        current = next;
    }

    return current;
}

PNMImage *shrinkImageHeight(PNMImage *image, int k)
{
    if (!image || k < 0) {
        return NULL;
    }

    /* Réduire la hauteur revient à réduire la largeur d'une image tournée. */
    PNMImage *rotated = rotate90Clockwise(image);
    if (!rotated) {
        return NULL;
    }

    PNMImage *shrunk = shrinkImageWidth(rotated, k);
    if (!shrunk) {
        freePNM(rotated);
        return NULL;
    }

    PNMImage *finalImage = rotate90CounterClockwise(shrunk);
    if (shrunk != rotated) {
        freePNM(shrunk);
    }
    freePNM(rotated);

    return finalImage;
}

/*
 * Cette fonction doit renvoyer l’énergie à la position (i, j) dans l’image img.
 * i est la ligne, j la colonne. Un voisin absent est remplacé par le pixel lui-même.
 */

double computePixelEnergyGradient(PNMImage *image, int i, int j)
{
    int width = (int)image->width;
    int height = (int)image->height;

    int leftCol = (j > 0) ? j - 1 : j;
    int rightCol = (j < width - 1) ? j + 1 : j;
    int upRow = (i > 0) ? i - 1 : i;
    int downRow = (i < height - 1) ? i + 1 : i;

    PNMPixel left = pixelAt(image, i, leftCol);
    PNMPixel right = pixelAt(image, i, rightCol);
    PNMPixel up = pixelAt(image, upRow, j);
    PNMPixel down = pixelAt(image, downRow, j);

    double energy = 0.0;
    int channels[3][2] = {
        {(int)left.red - (int)right.red, (int)up.red - (int)down.red},
        {(int)left.green - (int)right.green, (int)up.green - (int)down.green},
        {(int)left.blue - (int)right.blue, (int)up.blue - (int)down.blue}
    };

    for (int c = 0; c < 3; c++) {
        energy += (double)channels[c][0] * (double)channels[c][0];
        energy += (double)channels[c][1] * (double)channels[c][1];
    }

    return sqrt(energy);
}

/*
 * Cette fonction crée une nouvelle image obtenue en retirant de l’image img les
 * pixels dont l’abscisse est donnée par les positions dans le tableau seam donné
 * en argument (qui est supposé être renvoyé par la fonction
 * computeMinEnergyVerticalSeam). Plus précisément pour tout i ∈ {0,...,h−1},
 * le pixel (i, seam[i]) doit être retiré de l’image. Cette fonction ne doit pas
 * modifier l’image img passée en argument.
 */

PNMImage *cutImageWidth(PNMImage *image, int *minSeam)
{
    if (!image || !minSeam || image->width == 0) {
        return NULL;
    }

    size_t newWidth = image->width - 1;
    PNMImage *newImage = createPNM(newWidth, image->height);
    if (!newImage) {
        return NULL;
    }

    for (size_t row = 0; row < image->height; row++) {
        int removeCol = minSeam[row];
        size_t dest = 0;
        for (size_t col = 0; col < image->width; col++) {
            if ((int)col == removeCol) {
                continue;
            }
            newImage->data[row * newWidth + dest] =
                image->data[row * image->width + col];
            dest++;
        }
    }

    return newImage;
}

/*
 * Cette fonction prend comme argument une image et une fonction permettant de
 * calculer l’énergie d’un pixel et renvoie un tableau d’entiers de la taille de
 * la hauteur de l’image img contenant les abscisses des pixels appartenant à la
 * couture verticale d’énergie minimale dans l’image.
 *
 * Le tableau renvoyé est alloué dynamiquement et doit être libéré par l'appelant.
 */

int *computeMinEnergyVerticalSeam(PNMImage *image,
                                  double (*computePixelEnergy)(PNMImage *, int, int))
{
    if (!image || !computePixelEnergy || image->height == 0 || image->width == 0) {
        return NULL;
    }

    size_t height = image->height;
    size_t width = image->width;

    double *cost = malloc(height * width * sizeof(double));
    int *seam = malloc(height * sizeof(int));
    if (!cost || !seam) {
        free(cost);
        free(seam);
        return NULL;
    }

    for (size_t col = 0; col < width; col++) {
        cost[col] = computePixelEnergy(image, 0, (int)col);
    }

    for (size_t row = 1; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            double best = cost[(row - 1) * width + col];
            if (col > 0) {
                double left = cost[(row - 1) * width + (col - 1)];
                if (left < best) {
                    best = left;
                }
            }
            if (col + 1 < width) {
                double right = cost[(row - 1) * width + (col + 1)];
                if (right < best) {
                    best = right;
                }
            }
            cost[row * width + col] =
                computePixelEnergy(image, (int)row, (int)col) + best;
        }
    }

    size_t bestCol = 0;
    for (size_t col = 1; col < width; col++) {
        if (cost[(height - 1) * width + col] < cost[(height - 1) * width + bestCol]) {
            bestCol = col;
        }
    }
    seam[height - 1] = (int)bestCol;

    for (size_t row = height - 1; row > 0; row--) {
        size_t above = row - 1;
        size_t chosen = bestCol;
        if (bestCol > 0 &&
            cost[above * width + (bestCol - 1)] < cost[above * width + chosen]) {
            chosen = bestCol - 1;
        }
        if (bestCol + 1 < width &&
            cost[above * width + (bestCol + 1)] < cost[above * width + chosen]) {
            chosen = bestCol + 1;
        }
        bestCol = chosen;
        seam[above] = (int)bestCol;
    }

    free(cost);
    return seam;
}
