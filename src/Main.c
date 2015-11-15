#include "Main.h"

int main(void)
{
	Program* program = initialize("../../res/scripts/initialize.lua");
	program->window = SDL_CreateWindow(
		script_getstring(program->script, "window.title"), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		script_getinteger(program->script, "window.width"), 
		script_getinteger(program->script, "window.height"), 0
	);
	program->renderer = SDL_CreateRenderer(
		program->window, -1, 
		SDL_RENDERER_ACCELERATED | 
		SDL_RENDERER_PRESENTVSYNC
	);
	
	Array* arr = array_create();
	
	int x = 12;
	int y = 33;
	int z = -44;
	
	array_push(arr, 0, &x);
	array_push(arr, 0, &y);
	array_push(arr, 0, &x);
	array_push(arr, 0, &z);
	
	printf("length: %i\n", array_getlength(arr));
	system("pause");
	array_pop(arr, 2);
	
	printf("length: %i\n", array_getlength(arr));
	
	printf("values: %i, %i, %i", *(int*)array_getvalue(arr, 0), *(int*)array_getvalue(arr, 1), *(int*)array_getvalue(arr, 2));
	array_setvalue(arr, 1, NULL);
	printf("value: %p", array_getvalue(arr, 1));
	array_destroy(arr);

	int done = 0;
	while(!done)
	{
		done = process_events(program);
		render(program);
	}

	terminate(program);
	return 0;
}

Program* initialize(const char* init_script)
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
	program->keyboard_state = SDL_GetKeyboardState(NULL);
	//program->entities = array_create(8); //ERROR HERE!
	
	program->script = luaL_newstate();
	luaL_openlibs(program->script);
	if(luaL_dofile(program->script, init_script))
	{
		printf("Error: %s\n", lua_tostring(program->script, -1));
		return NULL;
	}

	return program;
}

void terminate(Program* program)
{
	SDL_DestroyRenderer(program->renderer);
	SDL_DestroyWindow(program->window);
	//array_destroy(program->entities); //ERROR HERE!
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