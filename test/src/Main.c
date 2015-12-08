#include "Main.h"

int main(void)
{
	if(!initialize_libraries())
	{
		return 1;
	}

	Program program = {
		script_initialize("../../res/scripts/initialize.lua"), 
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

	array_push(program.entities, 0, script_loadentity(program.script, "player", program.renderer));

	int done = 0;
	while(!done)
	{
		render(&program);
		done = process_events(&program);
	}

	for(int i = 0; i < array_getlength(program.entities); i++)
	{
		Entity* entity = array_getvalue(program.entities, i);
		Graphics_Component* gcomponent = entity_getcomponent(entity, COMPONENT_GRAPHICS);
		gcomponent_destroy(&gcomponent);
		
		Event_Component* ecomponent = entity_getcomponent(entity, COMPONENT_EVENT);
		free(ecomponent);
		entity_destroy(&entity);
	}

	array_destroy(&program.entities);
	lua_close(program.script);
	SDL_DestroyWindow(program.window);
	SDL_DestroyRenderer(program.renderer);
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
			
			case SDL_KEYDOWN:
				for(int i = 0; i < array_getlength(program->entities); i++)
				{
					Entity* entity = array_getvalue(program->entities, i);
					Event_Component* ecomponent = entity_getcomponent(entity, COMPONENT_EVENT);
					if(ecomponent != NULL)
					{
						int exist = 0;
						for(int i = 0; i < array_getlength(ecomponent->keys_down); i++)
						{
							char* key = array_getvalue(ecomponent->keys_down, i);
							if(*key == (char)event.key.keysym.sym)
							{
								exist = 1;
								break;
							}
						}
						
						if(!exist)
						{
							char* key = malloc(sizeof(char));
							if(key == NULL)
							{
								error_popup("Memory allocation error");
								return 0;
							}
							
							*key = (char)event.key.keysym.sym;
							array_push(ecomponent->keys_down, 0, key);
						}
					}
				}
			break;
			
			case SDL_KEYUP:
				for(int i = 0; i < array_getlength(program->entities); i++)
				{
					Entity* entity = array_getvalue(program->entities, i);
					Event_Component* ecomponent = entity_getcomponent(entity, COMPONENT_EVENT);
					if(ecomponent != NULL)
					{
						int exist = -1;
						for(int i = 0; i < array_getlength(ecomponent->keys_down); i++)
						{
							char* key = array_getvalue(ecomponent->keys_down, i);
							if(*key == (char)event.key.keysym.sym)
							{
								exist = i;
								break;
							}
						}
						
						if(exist >= 0)
						{
							array_pop(ecomponent->keys_down, exist);
						}
						
						lua_getglobal(program->script, entity_getname(entity));
						lua_getfield(program->script, -1, "event_component");
						lua_getfield(program->script, -1, "key_up");
						int function_pos = lua_gettop(program->script);
							
						script_pushentity(program->script, entity);
						lua_pushvalue(program->script, -1);
						lua_insert(program->script, function_pos);
						
						char buffer[2] = {(char)event.key.keysym.sym, '\0'};
						lua_pushstring(program->script, buffer);
						if(lua_pcall(program->script, 2, 0, 0))
						{
							error_popup(lua_tostring(program->script, -1));
						}
						
						script_popentity(program->script);
						lua_pop(program->script, 2);
					}
				}
			break;
		}
	}
	
	for(int i = 0; i < array_getlength(program->entities); i++)
	{
		Entity* entity = array_getvalue(program->entities, i);
		Event_Component* ecomponent = entity_getcomponent(entity, COMPONENT_EVENT);
		if(array_getlength(ecomponent->keys_down))
		{
			for(int i = array_getlength(ecomponent->keys_down) - 1; i >= 0; i--)
			{
				lua_getglobal(program->script, entity_getname(entity));
				lua_getfield(program->script, -1, "event_component");
				lua_getfield(program->script, -1, "key_down");
				int function_pos = lua_gettop(program->script);
								
				script_pushentity(program->script, entity);
				lua_pushvalue(program->script, -1);
				lua_insert(program->script, function_pos);
								
				char buffer[2] = {*(char*)(array_getvalue(ecomponent->keys_down, i)), '\0'};
				lua_pushstring(program->script, buffer);
								
				if(lua_pcall(program->script, 2, 0, 0))
				{
					error_popup(lua_tostring(program->script, -1));
				}
				script_popentity(program->script);
				lua_pop(program->script, 2);
			}
		}
	}
	
	return 0;
}

int render(Program* program)
{
	SDL_SetRenderDrawColor(program->renderer, 0, 255, 0, 255);
	SDL_RenderClear(program->renderer);
	
	for(int i = 0; i < array_getlength(program->entities); i++)
	{
		Entity* entity = array_getvalue(program->entities, i);
		Graphics_Component* gcomponent = entity_getcomponent(entity, COMPONENT_GRAPHICS);
		if(gcomponent != NULL)
		{
			gcomponent_render(gcomponent, program->renderer);
		}
	}
	
	SDL_RenderPresent(program->renderer);
	return 0;
}
