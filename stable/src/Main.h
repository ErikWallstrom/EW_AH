//EW_AH
#include "Array.h"
#include "Error.h"
#include "Script.h"
#include "Entity.h"
#include "Libraries.h"
#include "Components.h"

//Standard library
#include <math.h>
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

typedef struct
{
	lua_State* script;
	SDL_Window* window;
	SDL_Renderer* renderer;
	const Uint8* keyboard_state;
	
	Array* entities;
	
} Program;

int process_events(Program* program);
int render(Program* program);
