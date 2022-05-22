//gcc -o myprogram myprogram.c `sdl2-config --cflags --libs`
// j'en suis à essayer de colorer un point.
//https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/dessiner-dans-la-fenetre/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}



int main(int argc,char *argv[]){

	SDL_Window *window=NULL;
	SDL_Renderer* renderer=NULL;
	int statut=EXIT_FAILURE;
	SDL_Color orange={255,127,40,255};


	//initialisation de la SDL
	init(window, renderer,600,200);
	/*if(0!= SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stderr, "Erreur de SDL_Init: %s\n",SDL_GetError()); //écrit dans le flux de sortie standard d'erreur un message à propos de la dernière erreur rencontrée.
		goto Quit;
	}

	//création d'une fenêtre
	window=SDL_CreateWindow("testwindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600,200, SDL_WINDOW_SHOWN);

	if (NULL==window){
		fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
		goto Quit;
	}*/

	/*on agit sur la fenêtre ici*/

	
	/*renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(NULL==renderer){
		
		fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
		goto Quit;
	}*/

	/* C’est à partir de maintenant que ça se passe. */

	//colorie la fenêtre en orange
    if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }
    
    if(0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }

    
	SDL_Point point={0,0};

	

	
	SDL_Delay(2000); //la fenêtre s'affiche pendant 2s
	
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawPoint(renderer, 50, 50);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawPoint(renderer, 100, 100);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawPoint(renderer, 150, 150);
	SDL_RenderPresent(renderer);
*/
	SDL_RenderPresent(renderer);
	SDL_Delay(3000); //et se colore en orange pendant 3s

	statut=EXIT_SUCCESS;
	
Quit:

	if(NULL!= renderer){
		SDL_DestroyRenderer(renderer);
	}

	if(NULL!=window){
		SDL_DestroyWindow(window);
	}
	SDL_Quit(); //pour quitter la SDL
	return statut;
}
