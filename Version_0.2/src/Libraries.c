#include "Libraries.h"
#include "Error.h"
void Libraries_initialize(void)
{
	if(SDL_Init(SDL_INIT_VIDEO 
		| SDL_INIT_AUDIO))
		error(SDL_GetError());
	
	if(TTF_Init())
		error(SDL_GetError());
	
	if(SDLNet_Init())
		error(SDLNet_GetError());
	
	if(Mix_Init(MIX_INIT_MP3))
		error(SDL_GetError());
	
	if(!IMG_Init(IMG_INIT_JPG 
		| IMG_INIT_PNG))
		error(SDL_GetError());
}

void Libraries_terminate(void)
{
	IMG_Quit();
	Mix_Quit();
	SDLNet_Quit();
	TTF_Quit();
	SDL_Quit();
}
