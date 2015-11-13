//Standard library
#include <stdio.h>

//Lua 5.3
#include "../include/Lua_5.3/lua.h"
#include "../include/Lua_5.3/lualib.h"
#include "../include/Lua_5.3/lauxlib.h"

//SDL2
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/SDL2/SDL_net.h"
#include "../include/SDL2/SDL_mixer.h"
#include "../include/SDL2/SDL_image.h"

#undef main

int initialize_libraries(void)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		return 1;
	}
	if(TTF_Init())
	{
		return 1;
	}
	if(SDLNet_Init())
	{
		return 1;
	}
	if(!Mix_Init(MIX_INIT_MP3))
	{
		return 1;
	}
	if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		return 1;
	}
	
	return 0;
}

void terminate_libraries(void)
{
	IMG_Quit();
	Mix_Quit();
	SDLNet_Quit();
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if(initialize_libraries())
	{
		printf("Error: %s\n", SDL_GetError());
		return 1;
	}
	
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	if(luaL_dofile(L, "../../res/scripts/initialize.lua"))
	{
		printf("Error: %s\n", lua_tostring(L, -1));
		return 1;
	}

  	luaL_dostring(L, "__gettableval = window.title");
	lua_getglobal(L, "__gettableval");
	const char* window_title = lua_tostring(L, -1);
	lua_pop(L, 1);
	
	luaL_dostring(L, "__gettableval = window.width");
	lua_getglobal(L, "__gettableval");
	int window_width = lua_tointeger(L, -1);
	lua_pop(L, 1);
	
	luaL_dostring(L, "__gettableval = window.height");
	lua_getglobal(L, "__gettableval");
	int window_height = lua_tointeger(L, -1);
	lua_pop(L, 1);
	
	SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	SDL_Delay(5000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	lua_close(L);
	terminate_libraries();
	return 0;
}