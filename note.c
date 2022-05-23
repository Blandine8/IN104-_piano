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
        printf("%f\n",note[i]);
      ++i;
    }
    // close the file
    fclose(file);
    int indice_note=0;

    while (nb>note[indice_note]){
    	indice_note ++;

    }
    return indice_note;
}

