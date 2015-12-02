#include "Main.h"

Entity* load_script_entity(lua_State* L, SDL_Renderer* renderer, const char* name)
{
	Entity* entity = entity_create(name);
	lua_getglobal(L, name);
	if(lua_istable(L, -1))
	{
		//entity table exists
		lua_getfield(L, -1, "graphics_component");
		if(lua_istable(L, -1))
		{
			lua_getfield(L, -1, "file");
			const char* file = lua_tostring(L, -1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "rotation");
			double rotation = lua_tonumber(L, -1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "scale");
			double scale = lua_tonumber(L, -1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "width");
			int width = lua_tointeger(L, -1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "height");
			int height = lua_tointeger(L, -1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "x");
			double x = lua_tonumber(L, -1) - ((double)width / 2.0);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "y");
			double y = lua_tonumber(L, -1) - ((double)height / 2.0);
			lua_pop(L, 1);
			
			Graphics_Component* gcomponent = gcomponent_create(
				renderer, file, x, y, 
				width, height, scale, rotation
			);
			
			//entity contains graphics_component table
			lua_getfield(L, -1, "animations");
			if(lua_istable(L, -1))
			{
				//grahpics_component contains animations
				int stack_pos_1 = lua_gettop(L);
				lua_pushnil(L);
				while(lua_next(L, stack_pos_1))
				{
					//for each animation 
					SDL_Rect* frames = malloc(sizeof(SDL_Rect));
					if(frames == NULL)
					{
						error_popup("Memory allocation failed");
						return NULL;
					}
					int total_frames = 0;
					int delay = 0;
	
					int stack_pos_2 = lua_gettop(L);
					lua_pushnil(L);
					while(lua_next(L, stack_pos_2))
					{
						//values in each animation
						if(lua_type(L, -2) == LUA_TSTRING)
						{
							const char* key = lua_tostring(L, -2);
							if(!strcmp(key, "delay"))
							{
								delay = lua_tointeger(L, -1);
							}
						}
						else
						{
							if(lua_istable(L, -1))
							{
								total_frames++;
								
								lua_pushnumber(L, 1);
								lua_gettable(L, -2);
								frames = realloc(frames, sizeof(SDL_Rect) * total_frames);
								if(frames == NULL)
								{
									error_popup("Memory allocation failed");
									return NULL;
								}
								frames[total_frames - 1].x = (lua_tointeger(L, -1) - 1) * width;
								lua_pop(L, 1);
								
								lua_pushnumber(L, 2);
								frames[total_frames - 1].y = (lua_tointeger(L, -1) - 1) * height;
								lua_gettable(L, -2);

								frames[total_frames - 1].w = width;
								frames[total_frames - 1].h = height;
								lua_pop(L, 1);
							}
						}
						lua_pop(L, 1);
					}
					lua_pop(L, 1);
					gcomponent_addanimation(gcomponent, total_frames, frames, delay);
					free(frames);
				}
				lua_pop(L, 1);
			}
			lua_pop(L, 1);
			entity_addcomponent(entity, COMPONENT_GRAPHICS, gcomponent);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	
	return entity;
}

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

	array_push(program.entities, 0, load_script_entity(program.script, program.renderer, "player"));

	int done = 0;
	while(!done)
	{
		render(&program);
		done = process_events(&program);
	}

	lua_close(program.script);
	SDL_DestroyWindow(program.window);
	SDL_DestroyRenderer(program.renderer);
	array_destroy(&program.entities);
	
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
