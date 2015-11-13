#include "../include/SDL2/SDL.h"
#undef main

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_Window* window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	
	SDL_Delay(5000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}