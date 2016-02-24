#include <SDL_2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define x 3

typedef struct Program
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;
	
} Program;

int main(void)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		return EXIT_FAILURE;
	}
	
	Program p = {
		.window = SDL_CreateWindow(
			"Game Window",
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED,
			800, 600, 
			SDL_WINDOW_SHOWN
		),
		.renderer = SDL_CreateRenderer(
			p.window, -1,
			SDL_RENDERER_ACCELERATED | 
			SDL_RENDERER_PRESENTVSYNC | 
			SDL_RENDERER_TARGETTEXTURE
		),
		.running = true
	};
	if(!p.window || !p.renderer)
	{
		return EXIT_FAILURE;
	}
	
	SDL_Event event;
	while(p.running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				p.running = false;
			}
		}
		
		SDL_RenderClear(p.renderer);
		SDL_RenderPresent(p.renderer);
	}
	
	SDL_DestroyRenderer(p.renderer);
	SDL_DestroyWindow(p.window);
	SDL_Quit();
}
