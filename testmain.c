//gcc -o interface interface.c testmain.c interface.h `sdl2-config --cflags --libs`

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int main(){

	int note[3];
	note[0]=12;
	note[1]=11;
	note[2]=15;

	pianoColor(note);
	
	return 0;
}