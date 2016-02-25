#ifndef WINDOW_H
#define WINDOW_H

#include <SDL_2/SDL.h>
typedef struct
{
	SDL_Window* raw;
	SDL_Renderer* renderer;
	
} Window;

Window* Window_create(const char* title, 
					  int width, 
					  int height);
void Window_destroy(Window** window);

#endif