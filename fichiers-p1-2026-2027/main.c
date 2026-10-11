#include <stdio.h>
#include <stdlib.h>

#include "PNM.h"
#include "SeamCarving.h"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: ./SeamCarving input.pnm output.pnm kw kh\n");
        fprintf(stderr, "(kw, resp. kh, is the number of columns, resp. rows, to be removed from the image.)\n");
        return -1;
    }

    // Load image
    PNMImage *original = readPNM(argv[1]);
    if (!original)
    {
        fprintf(stderr, "Cannot load image '%s'\n", argv[1]);
        return -1;
    }

    // Seam carving
    int kw = atoi(argv[3]);
    int kh = atoi(argv[4]);

    if (kw >= (int)original->width)
    {
        fprintf(stderr, "kw should be strictly smaller than image width\n");
        freePNM(original);
        return -1;
    }
    if (kh >= (int)original->height)
    {
        fprintf(stderr, "kh should be strictly smaller than image height\n");
        freePNM(original);
        return -1;
    }

    PNMImage *new1 = original;
    if (kw > 0) {
        new1 = shrinkImageWidth(original, kw);
        if (!new1) {
            fprintf(stderr, "Cannot build new image.\n");
            exit(1);
        }
    }
    PNMImage *new2 = new1;

    if (kh>0) {
        new2 = shrinkImageHeight(new1, kh);
        if (!new2) {
            fprintf(stderr, "Cannot build new image.\n");
            exit(1);
        }
    }

    // Save and free
    writePNM(argv[2], new2);
    if (new2 != new1) {
        freePNM(new2);
    }
    if (new1 != original) {
        freePNM(new1);
    }
    freePNM(original);

    return 0;
}
