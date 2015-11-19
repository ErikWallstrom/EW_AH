//SDL2
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/SDL2/SDL_net.h"
#include "../include/SDL2/SDL_mixer.h"
#include "../include/SDL2/SDL_image.h"

int initialize_libraries(const char* init_script)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			SDL_GetError(), 
			NULL
		);
		return 1;
	}
	if(TTF_Init())
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			TTF_GetError(), 
			NULL
		);
		return 1;
	}
	if(SDLNet_Init())
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			SDLNet_GetError(), 
			NULL
		);
		return 1;
	}
	if(!Mix_Init(MIX_INIT_MP3))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			Mix_GetError(), 
			NULL
		);
		return 1;
	}
	if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			IMG_GetError(), 
			NULL
		);
		return 1;
	}
}

void terminate_libraries(Program* program)
{
	IMG_Quit();
	Mix_Quit();
	SDLNet_Quit();
	TTF_Quit();
	SDL_Quit();
}
