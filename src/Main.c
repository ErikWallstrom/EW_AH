#include "Main.h"

int main(void)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1", NULL);
	Program* program = initialize("../../res/scripts/initialize.lua");
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 2", NULL);
	program->window = SDL_CreateWindow(
		script_getstring(program->script, "window.title"), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		script_getinteger(program->script, "window.width"), 
		script_getinteger(program->script, "window.height"), 0
	);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 3", NULL);
	program->renderer = SDL_CreateRenderer(
		program->window, -1, 
		SDL_RENDERER_ACCELERATED | 
		SDL_RENDERER_PRESENTVSYNC
	);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 4", NULL);

	int done = 0;
	while(!done)
	{
		done = process_events(program);
		render(program);
	}

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 5", NULL);
	terminate(program);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 6", NULL);
	return 0;
}

Program* initialize(const char* init_script)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.1", NULL);
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		return NULL;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.2", NULL);
	if(TTF_Init())
	{
		return NULL;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.3", NULL);
	if(SDLNet_Init())
	{
		return NULL;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.4", NULL);
	if(!Mix_Init(MIX_INIT_MP3))
	{
		return NULL;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.5", NULL);
	if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		return NULL;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.6", NULL);
	
	Program* program = malloc(sizeof(program));
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.7", NULL);
	program->keyboard_state = SDL_GetKeyboardState(NULL);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.8", NULL);
	program->entities = array_create(8);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.9", NULL);
	
	program->script = luaL_newstate();
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.91", NULL);
	luaL_openlibs(program->script);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.92", NULL);
	if(luaL_dofile(program->script, init_script))
	{
		printf("Error: %s\n", lua_tostring(program->script, -1));
		return NULL;
	}
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SUKA BLYAD", "SUCCESS 1.93", NULL);
	return program;
}

void terminate(Program* program)
{
	SDL_DestroyRenderer(program->renderer);
	SDL_DestroyWindow(program->window);
	array_destroy(program->entities);
	lua_close(program->script);
	free(program);
	
	IMG_Quit();
	Mix_Quit();
	SDLNet_Quit();
	TTF_Quit();
	SDL_Quit();
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
	
	if(program->keyboard_state[SDL_SCANCODE_W])
	{
		
	}
	
	return 0;
}

int render(Program* program)
{
	SDL_SetRenderDrawColor(program->renderer, 0, 0, 255, 255);
	SDL_RenderClear(program->renderer);
	SDL_RenderPresent(program->renderer);
	
	return 0;
}