#include "Main.h"

int main(void)
{
	Program* program = Initialize("../../res/scripts/initialize.lua");
	program->window = SDL_CreateWindow(
		script_getstring(program->script, "window.title"), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		script_getinteger(program->script, "window.width"), 
		script_getinteger(program->script, "window.height"), 0
	);

	int done = 0;
	while(!done)
	{
		done = Process_Events(program);
		Render(program);
	}
	
	SDL_DestroyWindow(program->window);
	Terminate(program);
	return 0;
}

int Process_Events(Program* program)
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
	
	if(program->keyboard_state[SDL_SCANCODE_W])
	{
		
	}
	
	return 0;
}

void Render(Program* program)
{
	
}

Program* Initialize(const char* init_script)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		return NULL;
	}
	if(TTF_Init())
	{
		return NULL;
	}
	if(SDLNet_Init())
	{
		return NULL;
	}
	if(!Mix_Init(MIX_INIT_MP3))
	{
		return NULL;
	}
	if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		return NULL;
	}
	
	Program* program = malloc(sizeof(program));
	program->script = luaL_newstate();
	program->keyboard_state = SDL_GetKeyboardState(NULL);
	
	luaL_openlibs(program->script);
	if(luaL_dofile(program->script, init_script))
	{
		printf("Error: %s\n", lua_tostring(program->script, -1));
		return NULL;
	}
	
	return program;
}

void Terminate(Program* program)
{
	IMG_Quit();
	Mix_Quit();
	SDLNet_Quit();
	TTF_Quit();
	SDL_Quit();
	
	lua_close(program->script);
	free(program);
}
