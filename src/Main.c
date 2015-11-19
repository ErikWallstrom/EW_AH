#include "Main.h"

void test(Program* program)
{
	Entity* entity = malloc(sizeof(entity));
	entity->name = "player";
	if(!script_getnil(program->script, "player.graphics_component"))
	{
		Graphics_Component* gcomponent = malloc(sizeof(gcomponent));
		if(gcomponent == NULL)
		{
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR, 
				"Error", 
				"Memory allocation failed (test)", 
				NULL
			);
			
			return;
		}
		
		printf("%s\n", script_getstring(program->script, "player.graphics_component.file"));
		gcomponent->texture = IMG_LoadTexture(program->renderer, script_getstring(program->script, "player.graphics_component.file"));
		if(gcomponent->texture == NULL)
		{
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR, 
				"Error", 
				IMG_GetError(), 
				NULL
			);
			
			return;
		}
		printf("Hello4\n");
		gcomponent->x = script_getnumber(program->script, "player.graphics_component.x");
		printf("Hello5\n");
		gcomponent->y = script_getnumber(program->script, "player.graphics_component.y");
		printf("Hello6\n");
		gcomponent->width = script_getinteger(program->script, "player.graphics_component.width");
		printf("Hello7\n");
		gcomponent->height = script_getinteger(program->script, "player.graphics_component.height");
	
		printf("Hello8\n");
		array_push(entity->components, 0, gcomponent);
		printf("Hello9\n");
	}
	
	array_push(program->entities, 0, entity);
}

int main(void)
{
	initialize_libraries();
	
	lua_State* script = luaL_newstate();
	luaL_openlibs(script);
	if(luaL_dofile(script, "../../res/scripts/initialize.lua"))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(script, -1), 
			NULL
		);
		return 1;
	}
	printf("%s\n", script_getstring(script, "player.graphics_component.file"));
	
	Program program = {
		script, 
		SDL_CreateWindow(
			script_getstring(program.script, "window.title"), 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			script_getinteger(program.script, "window.width"), 
			script_getinteger(program.script, "window.height"), 0
		),
		SDL_CreateRenderer(
			program.window, -1, 
			SDL_RENDERER_ACCELERATED | 
			SDL_RENDERER_PRESENTVSYNC
		),
		SDL_GetKeyboardState(NULL),
		array_create(),
	};
	
	//test(&program);
	
	int done = 0;
	while(!done)
	{
		done = process_events(&program);
		render(&program);
	}

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
		Entity* entity = array_getvalue(program->entities, i);
		Graphics_Component* gcomponent = array_getvalue(entity->components, 0);
		 
		SDL_Rect dRect = {
			 (int)gcomponent->x, (int)gcomponent->y,
			 gcomponent->width, gcomponent->height
		};
		 
		SDL_RenderCopy(program->renderer, gcomponent->texture, NULL, &dRect);
	}
	
	SDL_RenderPresent(program->renderer);
	return 0;
}
