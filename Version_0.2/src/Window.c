#include "Window.h"
#include "Error.h"

#include <stdlib.h>

Window* Window_create(const char* title, 
					  int width, 
					  int height)
{
	Window* self = malloc(sizeof(Window));
	if(!self)
		error("Memory allocation error");
	
	self->raw = SDL_CreateWindow(
		title, 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height, 0
	);
	if(!self->raw)
		error(SDL_GetError());
	
	self->renderer = SDL_CreateRenderer(
		self->raw, -1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC |
		SDL_RENDERER_TARGETTEXTURE
	);
	if(!self->renderer)
		error(SDL_GetError());
	
	return self;
}

void Window_destroy(Window** window)
{
	Window* self = *window;
	SDL_DestroyRenderer(self->renderer);
	SDL_DestroyWindow(self->raw);
	free(self);
	*window = NULL;
}