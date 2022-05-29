//gcc -o interface interface.c testmain.c interface.h `sdl2-config --cflags --libs`

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "fftgsl.h"



int main(int argc, char* argv[]){
    char *nom=argv[1];
	int note[3];
	note[0]=numero_note(nom);
	note[1]=14;
	note[2]=16;
	 ;
	pianoColor(note);
	
	return 0;
}



    