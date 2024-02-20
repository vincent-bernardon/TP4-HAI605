
#include <math.h>
#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
using namespace std;

int getIndice(int i, int j, int nW, int nH){
    if(i<0){
        i=0;
    }
    if(i>nH-1){
        i=nH-1;
    }
    if(j<0){
        j=0;
    }
    if(j>nW-1){
        j=nW-1;
    }
    return i*nW+j;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, koi, indice;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }
printf("%i",indice);

//prendre tout les pixel sur ligne ou colone et en faire un graph
int Ij, Ii, G;


for (int i=0; i < nH; i++){

  for (int j=0; j < nW; j++){ 
    Ii=ImgIn[getIndice(i+1, j, nW, nH)]-ImgIn[getIndice(i, j, nW, nH)];
    Ij=ImgIn[getIndice(i, j+1, nW, nH)]-ImgIn[getIndice(i, j, nW, nH)];
    G=sqrt(pow(Ii,2)+pow(Ij,2));
    ImgOut[getIndice(i, j, nW, nH)]=G;
    //faire le +128 pour que ce soit plus visuelle mais pas besoin pour nous car cela nous arrenge d'avoir des negatifs afin d'avoir du noir dnas l'image
  }
}
   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);

   free(ImgIn); free(ImgOut);

   return 1;
}
