//gcc -o interface interface.c `sdl2-config --cflags --libs`
// j'en suis à essayer de colorer un point.
//https://zestedesavoir.com/tutoriels/1014/utiliser-la-sdl-en-langage-c/dessiner-dans-la-fenetre/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, 0, window, renderer))
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
	SDL_Color black={0,0,0,255};
	SDL_Color white={255,255,255,255};

	//initialisation de la SDL
	init(&window, &renderer,WINDOW_WIDTH,WINDOW_HEIGHT);

	/*............... C’est à partir de maintenant que ça se passe. .......................*/
	SDL_Surface *image=NULL;
	SDL_Texture *texture=NULL;

	image=SDL_LoadBMP("piano.bmp");

	if(NULL == image)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        goto Quit;
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }

	SDL_Rect rectangle;
    

    //on la charge en mémoire
    if (0!=SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h)){
    	fprintf(stderr, "Erreur SDL_QueryTexture : %s", SDL_GetError());
        goto Quit;
    }

    rectangle.x= (WINDOW_WIDTH-	rectangle.w)/2;
    rectangle.y=(WINDOW_HEIGHT - rectangle.h)/2;
    
    if (0!= SDL_RenderCopy(renderer, texture, NULL, &rectangle)){
    	fprintf(stderr, "Erreur SDL_RenderCopy : %s", SDL_GetError());
        goto Quit;
    }

    if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }

    int tnoire_w=40;
    int tnoire_h=199;

    SDL_Rect rectangle2;
    rectangle2.x=rectangle.x;
    rectangle2.y=rectangle.y;
    rectangle2.w= rectangle.w/7-tnoire_w/2;
    rectangle2.h=tnoire_h;
	
	if(0 != SDL_RenderFillRect(renderer, &rectangle2)){
    	fprintf(stderr, "Erreur SDL_RenderDrawLine : %s", SDL_GetError());
        goto Quit;
    }
    


    /*if(0 != SDL_RenderClear(renderer)) //efface le rendu
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }*/

	

	
	//SDL_Delay(2000); //la fenêtre s'affiche pendant 2s
	
	SDL_RenderPresent(renderer);
	SDL_Delay(10000); //et se colore en orange pendant 3s

	statut=EXIT_SUCCESS;

	/*...........................................................................................*/
	
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



/*//colorie la fenêtre en orange
    if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }

    if(0 != SDL_RenderDrawPoint(renderer, 50, 50)){
    	fprintf(stderr, "Erreur SDL_RenderDrawPoint : %s", SDL_GetError());
        goto Quit;
    }

    if(0 != SDL_RenderDrawLine(renderer, 50, 50,100,100)){
    	fprintf(stderr, "Erreur SDL_RenderDrawLine : %s", SDL_GetError());
        goto Quit;
    }


    SDL_Rect rectangle;
    rectangle.x=100;
    rectangle.y=100;
    rectangle.w=100;
    rectangle.h=100;

    if(0 != SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b,white.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        goto Quit;
    }

    if(0 != SDL_RenderFillRect(renderer, &rectangle)){
    	fprintf(stderr, "Erreur SDL_RenderDrawLine : %s", SDL_GetError());
        goto Quit;
    }*/