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
    // A compléter

    return NULL;
}



PNMImage *shrinkImageHeight(PNMImage *image, int k)
{
    // A compléter

    return NULL;
}

/*
Cette fonction doit renvoyer l’énergie à la position (i,j) dans l’image img
*/

double computePixelEnergyGradient(PNMImage *image, int i, int j)
{
    double energyGrad=0;
    int widht=image.widht;
    int heightgh=image.height;
    int order=i*widht+j;
    int left=order-1;
    int right=order+1;
    int up=order-widht;
    int down=order+widht;
    if (i==0 ){
        int left=order;
    }
    else if (i==widht_1 ){
        int right=order;
    }
    if (j==0){
        int up=order;
    }
    else if (j==height-1 ){
        int down=order;
    }
    
    energyGrad+=pow((image->data[left].red-image->data[right].red),2)+pow((image->data[up].red-image->data[down].red),2);
    energyGrad+=pow((image->data[left].green-image->data[right].green),2)+pow((image->data[up].green-image->data[down].green),2);
    energyGrad+=pow((image->data[left].blue-image->data[right].blue),2)+pow((image->data[up].blue-image->data[down].blue),2);


    return sqrt(energyGrad);
}

/*
Cette fonction crée une nouvelle image obtenue en retirant de l’image img les pixels dont l’abscisse est donnée par les
positions dans le tableau seam donné en argument (qui est supposé être renvoyé par la
fonction computeMinEnergyVerticalSeam). Plus précisément pour tout i ∈ {0,...,h−1},
le pixel (i,seam[i]) doit être retiré de l’image. Cette fonction ne doit pas modifier l’image img passée en argument.
*/

PNMImage *cutImageWidth(PNMImage *image, int *minSeam)
{
    newImage = CreatePNM(image.widht-1, PNMImage.height);
    unsigned numberDeleted=0;
    for (unsigned int i=0; i<image.height;i++){
        for (unsigned int j=0; j<image.widht;j++){
            if (j==minSeam[i]){
                numberDeleted++;
                continue;
            }
            newImage->data[i*image.widht+j-numberDeleted]=image->data[i*image.widht+j];

        }

    } 

    return *newImage;
}


/*
Cette fonction prend comme argument une image et une fonction permet
tant de calculer l’énergie d’un pixel et renvoie un tableau d’entiers de la taille de la hauteur
de l’image img contenant les abscisses des pixels appartenant à la couture verticale d’énergie
minimale dans l’image.
*/

int *computeMinEnergyVerticalSeam(PNMImage *image, double (*computePixelEnergy)(PNMImage *, int, int))
{
    int seam[image.height];
    double M[image.height][image.widht];
    for(unsigned i=0; i<image.widht;i++){
        M[0][i]=computePixelEnergy(*image,0,i); //Remplir première ligne avec les énergies
    }
    for (unsigned i=1;i<image.height;i++){
        M[i][0]=computePixelEnergy(*image, i, 0)+fmin(computePixelEnergy(*image,i-1,0),computePixelEnergy(*image,i-1,1));
        for (unsigned j=1;j<image.widht-1;j++){
            M[i][j]=computePixelEnergy(*image, i, j)+fmin(computePixelEnergy(*image,i-1,j-1), computePixelEnergy(*image,i-1,j),computePixelEnergy(*image,i-1,j));
        }
        M[i][image.widht-1]=computePixelEnergy(*image, i, image.widht-1)+fmin(computePixelEnergy(*image,i-1,j-1),computePixelEnergy(*image,i-1,j));
    }
    //On a une table M contenat l'énergie minimale pour arrievr au pixel correspondant en partant de la première ligne 

    return seam;
}


