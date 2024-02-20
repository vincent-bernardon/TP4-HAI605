

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



   OCTET *ImgIn, *ImgOut, *ImgTemp; //tableau d'octect contenant les couleurs de chaque pixel
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille); //calcul qui permet de représenter les différents pixel de l'img dans un tableau ID
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   allocation_tableau(ImgTemp, OCTET, nTaille);

   memcpy(ImgTemp, ImgIn, nTaille * sizeof(OCTET)); // Copie ImgIn dans ImgTemp


 for (int i=0; i < nH; i++) //hauteur donc ligne
    {
   for (int j=0; j < nW; j++) //largeur donc colone
     {
        //algorithme de dithering
        /*
        oldpixel := pixels[x][y]
        newpixel := find_closest_palette_color(oldpixel)
        pixels[x][y] := newpixel
        quant_error := oldpixel - newpixel
        pixels[x + 1][y    ] := pixels[x + 1][y    ] + quant_error × 7 / 16
        pixels[x - 1][y + 1] := pixels[x - 1][y + 1] + quant_error × 3 / 16
        pixels[x    ][y + 1] := pixels[x    ][y + 1] + quant_error × 5 / 16
        pixels[x + 1][y + 1] := pixels[x + 1][y + 1] + quant_error × 1 / 16

        find_closest_palette_color(oldpixel) = round(oldpixel / 255)

        @author https://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering
        */
        int indice = getIndice(i,j,nW,nH);
        int oldpixel = ImgTemp[indice];
        int newpixel = std::round(oldpixel / 255.0) * 255;
        ImgOut[indice] = newpixel;
        int quant_error = oldpixel - newpixel;
        ImgTemp[getIndice(i,j+1,nW,nH)] = ImgTemp[getIndice(i,j+1,nW,nH)] + quant_error * 7 / 16;
        ImgTemp[getIndice(i+1,j-1,nW,nH)] = ImgTemp[getIndice(i+1,j-1,nW,nH)] + quant_error * 3 / 16;
        ImgTemp[getIndice(i+1,j,nW,nH)] = ImgTemp[getIndice(i+1,j,nW,nH)] + quant_error * 5 / 16;
        ImgTemp[getIndice(i+1,j+1,nW,nH)] = ImgTemp[getIndice(i+1,j+1,nW,nH)] + quant_error * 1 / 16;
     }
    }
   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut); free(ImgTemp);

   return 1;
}


