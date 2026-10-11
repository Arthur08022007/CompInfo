
#ifndef _SEAMCARVING_H_
#define _SEAMCARVING_H_

#include "PNM.h"

/* ------------------------------------------------------------------------- *
 * Reduce the width of a PNM image by k pixels using the seam carving
 * algorithm.
 *
 * PARAMETERS
 * img          Pointer to a PNM image
 * k            The number of pixels to be removed (along the width axis).
 *              k can be assumed to be strictly lower than image width.
 *
 * RETURN
 * img          Pointer to a new PNM image
 * NULL         if an error occured
 *
 * Note: The original image must be preserved.
 * ------------------------------------------------------------------------- */

PNMImage *shrinkImageWidth(PNMImage *img, int k);

/* ------------------------------------------------------------------------- *
 * Reduce the height of a PNM image by k pixels using the seam carving
 * algorithm.
 *
 * PARAMETERS
 * img          Pointer to a PNM image
 * k            The number of pixels to be removed (along the height axis).
 *              k can be assumed to be strictly lower than image height.
 *
 * RETURN
 * img          Pointer to a new PNM image
 * NULL         if an error occured
 *
 * Note: The original image must be preserved.
 * ------------------------------------------------------------------------- */

PNMImage *shrinkImageHeight(PNMImage *img, int k);

/* ------------------------------------------------------------------------- *
 * Compute the energy of a pixel in an image
 *
 * PARAMETERS
 * img          Pointer to a PNM image
 * i,j          rows and columns of the pixel for each the energy needs
 *              to be computed.
 *
 * RETURN
 * Energy       The value of the energy at (i,j)
 *
 * ------------------------------------------------------------------------- */

double computePixelEnergyGradient(PNMImage *img, int i, int j);

/* ------------------------------------------------------------------------- *
 * Compute the minimal vertical energy seam in an image.
 *
 * PARAMETERS
 * img                   Pointer to a PNM image
 * computePixelEnergy    A pointer to a function that compute the energy
 *                       of a pixel
 *
 * RETURN
 * seam                  An array containing the seam. seam is an array of size
 *                       img->height with seam[i] the column of the minimal energy
 *                       seam at row i.
 *
 * ------------------------------------------------------------------------- */

int *computeMinEnergyVerticalSeam(PNMImage *img, double (*computePixelEnergy)(PNMImage *, int, int));

/* ------------------------------------------------------------------------- *
 * Generate a new image obtained by removing a vertical seam (as returned by
 * computeMinEnergySeam) from the image given as argument.
 * 
 *
 * PARAMETERS
 * img          Pointer to a PNM image
 * seam         An array of size img->height where seam[i] contains the
 *              the column of the pixel to be removed at row i.
 *
 * RETURN
 * image        Pointer to a new PNM image obtained by removing the seam from
 *              img.
 *
 * Note: The original image must be preserved.
 * ------------------------------------------------------------------------- */

PNMImage *cutImageWidth(PNMImage *img, int *seam);

#endif // _SEAMCARVING_H_
