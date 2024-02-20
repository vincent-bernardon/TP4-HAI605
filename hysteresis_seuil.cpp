
#include <math.h>
#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <cstring>
using namespace std;

int getIndice(int i, int j, int nW, int nH){
    i=std::min(std::max(i,0),nH-1);//pour gérè les côté de l'image 
    j=std::min(std::max(j,0),nW-1);
    return i*nW+j;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, SB, SH;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm SB(seuil bas) SH(seuil haut)\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&SB);
   sscanf (argv[4],"%d",&SH);



   OCTET *ImgIn, *ImgOut, *ImgTemp;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   allocation_tableau(ImgTemp, OCTET, nTaille);


//premier passage lecture de l’image de la norme des gradients : si norme du gradient <= SB alors 0, si norme du gradient >= SH alors 255
for (int i=0; i < nH; i++){ //hauteur donc ligne

  for (int j=0; j < nW; j++){ //largeur donc colonne
    if(ImgIn[getIndice(i, j, nW, nH)]<=SB){
        ImgTemp[getIndice(i, j, nW, nH)]=0;
    }else if(ImgIn[getIndice(i, j, nW, nH)]>SH){
        ImgTemp[getIndice(i, j, nW, nH)]=255; //couleur blanche
    }else{
        ImgTemp[getIndice(i, j, nW, nH)]=128;
    }
  }
}
int nbtentative=100;
bool onContinue =true;
while(onContinue){
    for (int i=0; i < nH; i++){ //hauteur donc ligne

    for (int j=0; j < nW; j++){ //largeur donc colonne
    bool voisin = false;
    if(ImgTemp[getIndice(i, j, nW, nH)]!=128){
        ImgOut[getIndice(i, j, nW, nH)]=0;
        continue;
    }
        for(int dx=-1; dx<=1;dx++){
        for(int dy=-1; dy<=1; dy++){
            if(ImgTemp[getIndice(i+dx, j+dy, nW, nH)]==255){
                voisin=true;
                break;
            }
        }
        if(voisin==true){
            break;
        }
        }
        if(voisin){
            ImgOut[getIndice(i, j, nW, nH)]=255;
        }
    }
    } 
    
    for(int i=0;i<nTaille;i++){
        if(ImgOut[i]!=128){
            onContinue=false;
        }
    }
    nbtentative--;
    if(nbtentative==0){
        break;
    }
}
char nn[250] = "interm_";
    ecrire_image_pgm(strcat(nn, cNomImgEcrite), ImgTemp,  nH, nW);
   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);

   free(ImgIn); free(ImgOut), free(ImgTemp);

   return 1;
}
