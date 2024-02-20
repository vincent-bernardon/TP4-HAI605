
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, koi, indice;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm ligneOuColone(0 ligne et 1 colone) indice\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&koi); //0 ligne et 1 colone
   sscanf (argv[4],"%d",&indice);

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
FILE *histo; 
histo = fopen("profil.dat", "wb");
for (int i=0; i < nH; i++){

  for (int j=0; j < nW; j++)
  { 
    if(koi==0 && i==indice){
      fprintf(histo, "%d\n",ImgIn[i*nW+j]);
    }
    else if(koi==1 && j==indice){
      fprintf(histo, "%d\n",ImgIn[i*nW+j]);
    }else{
      ImgOut[i*nW+j]=ImgIn[i*nW+j];
    }

  }
}
   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);

   free(ImgIn); free(ImgOut);

   return 1;
}
