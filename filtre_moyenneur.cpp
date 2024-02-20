

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
using namespace std;

int getIndice(int i, int j, int nW, int nH){
    i=std::min(std::max(i,0),nH-1);//pour gérè les côté de l'image 
    j=std::min(std::max(j,0),nW-1);
    return i*nW+j;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);



   OCTET *ImgIn, *ImgOut; //tableau d'octect contenant les couleurs de chaque pixel
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille); //calcul qui permet de représenter les différents pixel de l'img dans un tableau ID
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);


 for (int i=0; i < nH; i++) //hauteur donc ligne
    {
   for (int j=0; j < nW; j++) //largeur donc colone
     {
        int somme=0;
       for(int dx=-1; dx<=1;dx++){
        for(int dy=-1; dy<=1; dy++){
            somme +=ImgIn[getIndice(i+dx, j+dy, nW, nH)];
        }
       }
       somme=((somme)/(9));
       ImgOut[getIndice(i,j,nW,nH)]=somme;
     }
    }
   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}


