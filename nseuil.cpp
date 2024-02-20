#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

// Fonction de comparaison pour qsort
int compare(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nb_seuil;

  if (argc < 5) 
  {
    printf("Usage: ImageIn.pgm ImageOut.pgm nb_de_seuil Seuil1 Seuil2 ... SeuilN\n"); 
    exit (1);
  }

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);
  sscanf (argv[3],"%d",&nb_seuil);

  if(nb_seuil < 2 || nb_seuil > argc - 4){
    printf("trop ou pas assez de seuil");
    exit(1);
  }

  int* seuils = (int*) malloc(nb_seuil * sizeof(int));
  for(int i = 0; i < nb_seuil; i++) {
    sscanf(argv[i + 4], "%d", &seuils[i]);
  }

  // Tri du tableau de seuils
  qsort(seuils, nb_seuil, sizeof(int), compare);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for (int i=0; i < nH; i++)
    for (int j=0; j < nW; j++)
    {
      int pixel = ImgIn[i*nW+j];
      for(int k = 0; k < nb_seuil; k++) {
        if(pixel < seuils[k]) {
          ImgOut[i*nW+j] = k * (255 / (nb_seuil - 1));
          break;
        }
        if(k == nb_seuil - 1) {
          ImgOut[i*nW+j] = 255;
        }
      }
    }

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn); free(ImgOut); free(seuils);

  return 1;
}