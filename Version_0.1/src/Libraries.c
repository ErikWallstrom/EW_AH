#include "Libraries.h"

//SDL2
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/SDL2/SDL_net.h"
#include "../include/SDL2/SDL_mixer.h"
#include "../include/SDL2/SDL_image.h"

int initialize_libraries(void)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			SDL_GetError(), 
			NULL
		);
		return 0;
	}
	if(TTF_Init())
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			TTF_GetError(), 
			NULL
		);
		return 0;
	}
	if(SDLNet_Init())
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			SDLNet_GetError(), 
			NULL
		);
		return 0;
	}
	/*if(!Mix_Init(MIX_INIT_MP3)) //Fucks linux up
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			Mix_GetError(), 
			NULL
		);
		return 0;
	}*/
	if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			IMG_GetError(), 
			NULL
		);
		return 0;
	}
	
	return 1;
}

void terminate_libraries(void)
{
	IMG_Quit();
	//Mix_Quit();
	SDLNet_Quit();
	TTF_Quit();
	SDL_Quit();
}
