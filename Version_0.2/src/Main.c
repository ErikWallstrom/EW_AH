#include <stdlib.h>
#include <stdio.h>

#include "Libraries.h"
#include "Window.h"

#undef main
int main(void)
{
	Libraries_initialize();
	Window* window = Window_create(
		"Game Window", 
		800, 600
	);
	
	while(1)
	{
		SDL_RenderClear(window->renderer);
		SDL_RenderPresent(window->renderer);
	}
	
	SDL_Delay(3500);
	Window_destroy(&window);
	Libraries_terminate();
}
