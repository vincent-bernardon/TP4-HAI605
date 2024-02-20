#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
using namespace std;

int getIndice(int i, int j, int nW, int nH){
    i=std::min(std::max(i,0),nH-1);
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

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   // Matrice de convolution pour le filtre gaussien
   int filter[3][3] = {
       {1, 2, 1},
       {2, 4, 2},
       {1, 2, 1}
   };

   for (int i=0; i < nH; i++)
   {
       for (int j=0; j < nW; j++)
       {
           int sum = 0;
           for(int dx=-1; dx<=1; dx++){
               for(int dy=-1; dy<=1; dy++){
                   int x = std::min(std::max(i+dx,0),nH-1);
                   int y = std::min(std::max(j+dy,0),nW-1);
                   sum += ImgIn[getIndice(x, y, nW, nH)] * filter[dx+1][dy+1];
               }
           }
           ImgOut[getIndice(i,j,nW,nH)] = sum / 16; // La somme des poids du filtre gaussien est 16
       }
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}