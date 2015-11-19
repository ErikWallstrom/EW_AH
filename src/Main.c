#include "Main.h"

int main(void)
{
	initialize_libraries();
	
	lua_State* script = luaL_newstate();
	luaL_openlibs(script);
	if(luaL_dofile(script, "initialize.lua"))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return NULL;
	}
	
	Program program = {
		script, 
		SDL_CreateWindow(
			script_getstring(program->script, "window.title"), 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			script_getinteger(program->script, "window.width"), 
			script_getinteger(program->script, "window.height"), 0
		),
		SDL_CreateRenderer(
			program->window, -1, 
			SDL_RENDERER_ACCELERATED | 
			SDL_RENDERER_PRESENTVSYNC
		),
		SDL_GetKeyboardState(NULL),
		array_create(),
		array_create()
	};
	
	int done = 0;
	while(!done)
	{
		done = process_events(program);
		render(program);
	}
	
	array_destroy(program.textures);
	array_destroy(program.entities);
	SDL_DestroyRenderer(program.renderer);
	SDL_DestroyWindow(program.window);
	
	terminate_libraries();
	return 0;
}

int process_events(Program* program)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				return 1;
			break;
		}
	}
	
	return 0;
}

int render(Program* program)
{
	SDL_SetRenderDrawColor(program->renderer, 0, 0, 255, 255);
	SDL_RenderClear(program->renderer);
	
	for(int i = 0; i < array_getlength(program->entities); i++)
	{
		 
	}
	
	SDL_RenderPresent(program->renderer);
	return 0;
}
