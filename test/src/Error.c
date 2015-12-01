#include "Error.h"
#include "../include/SDL2/SDL.h"
#include <stdio.h>

void error_popup(const char* message)
{
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR, 
		"Error", 
		message, 
		NULL
	);
}

void error_print(const char* message)
{
	printf("Error: %s\n", message);
}
