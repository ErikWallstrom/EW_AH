//Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

const char* lua_tostring(lua_State* L, const char* variable_name)
{
	char script[32] = "__getvariable=";
	strcat(script, variable_name);
	luaL_dostring(L, script)
	lua_getglobal( L, "__getvariable" );  

	const char* string = lua_tostring(L, -1);
	lua_pop(L, 1);
	
	return string;
}

int lua_tostring(lua_State* L, const char* variable_name)
{
	char script[32] = "__getvariable=";
	strcat(script, variable_name);
	luaL_dostring(L, script)
	lua_getglobal( L, "__getvariable" );  

	char* string = lua_tostring(L, -1);
	lua_pop(L, 1);
	
	return string;
}

int lua_tostring(lua_State* L, const char* variable_name)
{
	char script[32] = "__getvariable=";
	strcat(script, variable_name);
	luaL_dostring(L, script)
	lua_getglobal( L, "__getvariable" );  

	char* string = lua_tostring(L, -1);
	lua_pop(L, 1);
	
	return string;
}

int lua_tostring(lua_State* L, const char* variable_name)
{
	char script[32] = "__getvariable=";
	strcat(script, variable_name);
	luaL_dostring(L, script)
	lua_getglobal( L, "__getvariable" );  

	char* string = lua_tostring(L, -1);
	lua_pop(L, 1);
	
	return string;
}

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

int main(void)
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
	
	printf("%s\n", lua_getstring(L, "player.file"));

	lua_close(L);
	terminate_libraries();
	return 0;
}