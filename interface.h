#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

int colorNote(SDL_Renderer *renderer, SDL_Rect rectangle, SDL_Color orange, int note);

void pianoColor(int* note); //prend en argument un tableau de 3 entiers. (de 1 à 7 = de do à si; de 11 à 16 = de do# à la#; 13 à ne pas utiliser !! )



#endif
