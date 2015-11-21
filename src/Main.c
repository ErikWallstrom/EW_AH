#include "Main.h"

void test(Program* program)
{
	Entity* entity = malloc(sizeof(Entity));
	entity->name = "player";
	entity->components = array_create();
	if(!script_getnil(program->script, "player.graphics_component"))
	{
		Graphics_Component* gcomponent = malloc(sizeof(Graphics_Component));
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

		gcomponent->x = script_getnumber(program->script, "player.graphics_component.x");
		gcomponent->y = script_getnumber(program->script, "player.graphics_component.y");
		gcomponent->width = script_getinteger(program->script, "player.graphics_component.width");
		gcomponent->height = script_getinteger(program->script, "player.graphics_component.height");
	
		array_push(entity->components, 0, gcomponent);
	}
	
	array_push(program->entities, 0, entity);
}

lua_State* initialize_script(const char* file)
{
	lua_State* L = luaL_newstate();
	if(L == NULL)
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return NULL;
	}
	
	luaL_openlibs(L);
	if(luaL_dofile(L, file))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return NULL;
	}
	
	return L;
}

int main(void)
{
	if(initialize_libraries())
	{
		return 1;
	}

	Program program = {
		initialize_script("../../res/scripts/initialize.lua"), 
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
	
	test(&program);
	
	int done = 0;
	while(!done)
	{
		render(&program);
		done = process_events(&program);
	}

	lua_close(program.script);
	SDL_DestroyWindow(program.window);
	SDL_DestroyRenderer(program.renderer);
	array_destroy(program.entities);
	
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
