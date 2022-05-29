#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int trouver_la_note(int nb){
    FILE* file=fopen("note.txt","r+");
    if (file == NULL)
    {
        printf("Error: could not open file");
        return 1;
    }
    double note[88];
    int i=1;
    fscanf(file,"%le",&note[0]);
    while (i<88){
        fscanf(file,"%lf",&note[i]);
        //printf("%f\n",note[i]);
      ++i;
    }
    // note représente toutes les fréquences de chaque note
    fclose(file);
    int indice_note=0;

    while (nb>note[indice_note]){
    	indice_note ++;

    }
    int numero;
    // indice note représente le numéro de la note pour wiképedia
    // pour l'instant le piano à 12 notes, donc on modifie le numéro modulo 12 pour qu'il corresponde au numéro de notre clavier (attetion au touche blance (de 1à7) et noir de (11à16))
    if (indice_note%12==4){
        numero =1;
    }

     if (indice_note%12==6){
        numero =2;
    }
     if (indice_note%12==8){
        numero =3;
    }
     if (indice_note%12==9){
        numero =4;
    }
     if (indice_note%12==11){
        numero =5;
    } 
    if (indice_note%12==1){
        numero =6;
    } 
    if (indice_note%12==3){
        numero =7;
    } 
    if (indice_note%12==5){
        numero =11;
    }
        if (indice_note%12==7){
        numero =12;
    }
    if (indice_note%12==10){
        numero =14;
    }
    if (indice_note%12==0){
        numero =15;
    }
    if (indice_note%12==2){
        numero =16;
    }













      if (indice_note%12==8){
        numero =3;
    } 



    return numero;
}

