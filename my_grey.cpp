// test_couleur.cpp : Seuille une image en 3 ou 4 niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S1, nb_seuil, S2, S3;
  
  if (argc != 7) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil1 Seuil2 **Seuil3** nb_de_seuil\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S1);
   sscanf (argv[4],"%d",&S2);
   sscanf (argv[5],"%d",&S3);
   sscanf (argv[6],"%d",&nb_seuil);

   if(nb_seuil<3||nb_seuil>4){
    printf("trop ou pas assez de seuil");
    exit(1);
   }


   OCTET *ImgIn, *ImgOut; //tableau d'octect contenant les couleurs de chaque pixel
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille); //calcul qui permet de représenter les différents pixel de l'img dans un tableau ID
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);



 for (int i=0; i < nH; i++) //hauteur donc ligne
   for (int j=0; j < nW; j++) //largeur donc colone
     {
        if(nb_seuil == 3){
            if ( ImgIn[i*nW+j] < S1)ImgOut[i*nW+j]=0; 
            else if (ImgIn[i*nW+j] < S2) ImgOut[i*nW+j]=128;
            else ImgOut[i*nW+j]=255;  
        }
        if(nb_seuil == 4){
            if ( ImgIn[i*nW+j] < S1)ImgOut[i*nW+j]=0; 
            else if (ImgIn[i*nW+j] < S2) ImgOut[i*nW+j]=64;
            else if (ImgIn[i*nW+j] < S3) ImgOut[i*nW+j]=128;
            else ImgOut[i*nW+j]=255;  
        }
       
     }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
