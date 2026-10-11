#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "PNM.h"
#include "SeamCarving.h"


/*
Ces fonctions renvoient une réduction de l’image img donnée en argument de k pixels res
pectivement en largeur et en hauteur en utilisant la procédure décrite dans la section 1. Ces
fonctions doivent créer et renvoyer une nouvelle image et ne doivent pas modifier l’image
img passée en argument
*/

PNMImage *shrinkImageWidth(PNMImage *image, int k) //*image est un pointeur vers
{
    PNMImage *prevImage=image;
    for (int i=0;i<k;i++){
        int *seam=computeMinEnergyVerticalSeam(prevImage, computePixelEnergyGradient);
        PNMImage *newImage=cutImageWidth(prevImage, seam);
        if(prevImage != image){
            freePNM(prevImage);
        }
        free(seam);
        prevImage=newImage;
        
    }

    return prevImage;
}




PNMImage *shrinkImageHeight(PNMImage *image, int k)
{
    PNMImage *rotatedImage=createPNM(image->height,image->width);
    for (size_t j=0;j<image->width;j++){
        for (size_t i=0;i<image->height;i++){
            rotatedImage->data[j*rotatedImage->width+i]=image->data[i*image->width+j];
        }
    }
    PNMImage *shrinkedRotImage = shrinkImageWidth(rotatedImage, k);

    PNMImage *finalImage=createPNM(image->width,image->height-k);
    for (size_t j=0;j<image->width;j++){
        for (size_t i=0;i<image->height-k;i++){
            finalImage->data[i*finalImage->width+j]=shrinkedRotImage->data[j*shrinkedRotImage->width+i];
        }
    }

    if (shrinkedRotImage != rotatedImage){
        freePNM(shrinkedRotImage);
    }
    freePNM(rotatedImage);

    return finalImage;
}

/*
Cette fonction doit renvoyer l’énergie à la position (i,j) dans l’image img
*/

double computePixelEnergyGradient(PNMImage *image, int i, int j)
{
    double energyGrad=0;
    int width=image->width;
    int height=image->height;
    int order=i*width+j;
    int left=order-1;
    int right=order+1;
    int up=order-width;
    int down=order+width;
    if (j==0 ){
        left=order;
    }
    else if (j==width-1 ){
        right=order;
    }
    if (i==0){
        up=order;
    }
    else if (i==height-1 ){
        down=order;
    }

    int hr= image->data[left].red-image->data[right].red;
    int hg=image->data[left].green-image->data[right].green;
    int hb=image->data[left].blue-image->data[right].blue;

    int vr=image->data[up].red-image->data[down].red;
    int vg=image->data[up].green-image->data[down].green;
    int vb=image->data[up].blue-image->data[down].blue;
    
    energyGrad=sqrt(hr*hr+hg*hg+hb*hb+vr*vr+vg*vg+vb*vb);


    return energyGrad;
}

/*
Cette fonction crée une nouvelle image obtenue en retirant de l’image img les pixels dont l’abscisse est donnée par les
positions dans le tableau seam donné en argument (qui est supposé être renvoyé par la
fonction computeMinEnergyVerticalSeam). Plus précisément pour tout i ∈ {0,...,h−1},
le pixel (i,seam[i]) doit être retiré de l’image. Cette fonction ne doit pas modifier l’image img passée en argument.
*/

PNMImage *cutImageWidth(PNMImage *image, int *minSeam)
{
    PNMImage *newImage = createPNM(image->width-1, image->height);
    unsigned numberDeleted=0;
    for (size_t i=0; i<image->height;i++){
        for (size_t j=0; j<image->width;j++){
            if ((int)j==minSeam[i]){
                numberDeleted++;
                continue;
            }
            newImage->data[i*image->width+j-numberDeleted]=image->data[i*image->width+j];

        }

    } 

    return newImage;
}


/*
Cette fonction prend comme argument une image et une fonction permet
tant de calculer l’énergie d’un pixel et renvoie un tableau d’entiers de la taille de la hauteur
de l’image img contenant les abscisses des pixels appartenant à la couture verticale d’énergie
minimale dans l’image.
*/

int *computeMinEnergyVerticalSeam(PNMImage *image, double (*computePixelEnergy)(PNMImage *, int, int))
{
    double M[image->height][image->width];
    for(unsigned i=0; i<image->width;i++){
        M[0][i]=computePixelEnergy(image,0,i); //Remplir première ligne avec les énergies
    }
    for (unsigned i=1;i<image->height;i++){
        M[i][0]=computePixelEnergy(image, i, 0)+fmin(computePixelEnergy(image,i-1,0),computePixelEnergy(image,i-1,1));
        for (unsigned j=1;j<image->width-1;j++){
            M[i][j]=computePixelEnergy(image, i, j)+fmin(computePixelEnergy(image,i-1,j-1), fmin(computePixelEnergy(image,i-1,j),computePixelEnergy(image,i-1,j)));
        }
        M[i][image->width-1]=computePixelEnergy(image, i, image->width-1)+fmin(computePixelEnergy(image,i-1,image->width-1),computePixelEnergy(image,i-1,image->width-2));
    }
    //On a une table M contenat l'énergie minimale pour arriver au pixel correspondant en partant de la première ligne 

    int *seam=malloc(image->height*sizeof(int));
    
    // On cherche le M de la dernière ligne de plus petite valeur
    int min=0;
    for (size_t i=1; i<image->width;i++){
        if (M[image->height-1][i]<M[image->height-1][min]){
            min=i;
        }
    }
    seam[image->height-1]=min;

    for (size_t j=2; j<=image->height; j++){
        for (int i=min-1;i<=min+1;i++){
            if (i==(int)(image->width)){
                continue;
            }
            if (i==-1){
                continue;
            }
            if (M[image->height-j][i]<M[image->height-j][min]){
                min=i;
            } 
        }
        seam[image->height-j]=min;
    }



    return seam;
}


