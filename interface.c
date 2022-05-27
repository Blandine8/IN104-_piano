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

int colorNote(SDL_Renderer *renderer, SDL_Rect rectangle, SDL_Color orange, int note){

	if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        return -1;
    }
    int posx= rectangle.x+7 +(note-1)* (rectangle.w-7)/7;
    int posy=rectangle.y;
    int tnoire_w=39;
    int tnoire_h=198;

    SDL_Rect tHaut;
    SDL_Rect tBas;
    SDL_Rect tNoire;

    tBas.w= rectangle.w/7-7;
    tBas.h=rectangle.h-tnoire_h;
    tBas.x=posx;
    tBas.y=rectangle.y+tnoire_h;

    tNoire.w=tnoire_w;
    tNoire.h=tnoire_h;
    tNoire.y=rectangle.y;
    

    if ((note==1)|(note==4)){
    	tHaut.x=posx;
    	tHaut.y=rectangle.y;
    	tHaut.w= rectangle.w/7-tnoire_w/2-2;
    	tHaut.h=tnoire_h;	
    }

    else{
    	if ((note ==2) | (note==5) | (note==6)){
    		tHaut.x=posx+tnoire_w/2-7;
    		tHaut.y=rectangle.y;
    		tHaut.w= (rectangle.w-7)/7-tnoire_w+7;
    		tHaut.h=tnoire_h;

    	}

    	else{
    		if ((note==3) | (note==7)){
    			tHaut.x=posx+tnoire_w/2-5;
	    		tHaut.y=rectangle.y;
	    		tHaut.w= rectangle.w/7-tnoire_w/2-2;
	    		tHaut.h=tnoire_h;

    		}

    		else {
    			tNoire.x= rectangle.x + (note-11)*(rectangle.w/7)+ rectangle.w/7-tnoire_w/2+2;		

    		}
    
    	}
    		}
    
    
	
	if(0 != SDL_RenderFillRect(renderer, &tHaut)){
    	fprintf(stderr, "Erreur SDL_RenderDrawLine : %s", SDL_GetError());
        return -1;
    }

    
    
    
    
    if(0 != SDL_RenderFillRect(renderer, &tBas)){
    	fprintf(stderr, "Erreur SDL_RenderDrawLine : %s", SDL_GetError());
        return -1;
    }

    if(0 != SDL_RenderFillRect(renderer, &tNoire)){
    	fprintf(stderr, "Erreur SDL_RenderDrawLine : %s", SDL_GetError());
        return -1;
    }

    return 0;
}


void pianoColor(int* note){


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

    for (int i=0; i<3; i++){

    	if (note[i] !=0 ){

    	
    		if (0!= colorNote(renderer, rectangle, orange,note[i])){
    			goto Quit;
    		}
    	}
    	
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
	//return statut;
}

