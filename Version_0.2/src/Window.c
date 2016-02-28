#include "Window.h"
#include "String.h"
#include "Error.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct Window
{
	SDL_Window* raw;
	SDL_Renderer* renderer;
	String* title;
	int width, height;
};

Window* Window_create(const char* title, 
					  int width, 
					  int height)
{
	assert(title);
	Window* self = malloc(sizeof(Window));
	if(!self)
		error(ERROR_ALLOC);
	self->raw = SDL_CreateWindow(
		title, 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height, 0);
	if(!self->raw)
		error(SDL_GetError());
	self->renderer = SDL_CreateRenderer(
		self->raw, -1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC |
		SDL_RENDERER_TARGETTEXTURE);
	if(!self->renderer)
		error(SDL_GetError());
	self->width = width;
	self->height = height;
	self->title = String_create(title);
	return self;
}

void Window_destroy(Window** window)
{
	assert(window && (*window));
	Window* self = *window;
	SDL_DestroyRenderer(self->renderer);
	SDL_DestroyWindow(self->raw);
	String_destroy(&self->title);
	free(self);
	*window = NULL;
}

SDL_Window* Window_get_raw(const Window* self)
{
	assert(self);
	return self->raw;
}

SDL_Renderer* Window_get_renderer(const Window* self)
{
	assert(self);
	return self->renderer;
}

int Window_get_width(const Window* self)
{
	assert(self);
	return self->width;
}

int Window_get_height(const Window* self)
{
	assert(self);
	return self->height;
}

const char* Window_get_title(const Window* self)
{
	assert(self);
	return String_get(self->title);
}

void Window_set_width(Window* self, int width)
{
	assert(self);
	SDL_SetWindowSize(self->raw, width, self->height);
	self->width = width;
}

void Window_set_height(Window* self, int height)
{
	assert(self);
	SDL_SetWindowSize(self->raw, self->width, height);
	self->height = height;
}

void Window_set_title(Window* self, const char* title)
{
	assert(self && title);
	SDL_SetWindowTitle(self->raw, title);
	String_set(self->title, title);
}

