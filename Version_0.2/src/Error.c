#include "Error.h"
#include <stdlib.h>
#include <SDL_2/SDL.h>
void error(const char* msg)
{
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR, 
		"Error", msg, NULL);
	exit(EXIT_FAILURE);
}
