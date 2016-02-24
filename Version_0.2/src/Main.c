#include <SDL_2/SDL.h>
#include <Lua_5.3/lauxlib.h>
#include <Lua_5.3/lualib.h>

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	lua_State* L = luaL_newstate();
	if(L)
	{
		luaL_openlibs(L);
		if(luaL_dofile(L, "../../res/scripts/main.lua"))
		{
			return EXIT_FAILURE;
		}
	}
	
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		return EXIT_FAILURE;
	}
	
	SDL_Window* window = SDL_CreateWindow(
		"Hello World",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600, 0
	);
	
	SDL_Delay(3500);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
