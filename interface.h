#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

int colorNote(SDL_Renderer *renderer, SDL_Rect rectangle, SDL_Color orange, int note);

void pianoColor(int* note);



#endif
