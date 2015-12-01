#include "Main.h"
/*
Entity* load_entity(lua_State* L, const char* name, SDL_Renderer* renderer)
{
	Entity* entity = entity_create(name);
	lua_getglobal(L, name);
	int stack_pos_name = lua_gettop(L);
	if(lua_istable(L, stack_pos_name))
	{
		lua_getfield(L, stack_pos_name, "image_component");
		int stack_pos_image_component = lua_gettop(L);
		if(lua_istable(L, stack_pos_image_component))
		{
			Image_Component* icomponent = malloc(sizeof(Image_Component));
			if(icomponent == NULL)
			{
				error_popup("Memory allocation failed (load_entity)");
				return NULL;
			}
			
			lua_getfield(L, stack_pos_image_component, "file");
			icomponent->texture = IMG_LoadTexture(renderer, luaL_checkstring(L, -1));
			lua_pop(L, 1);
			
			lua_getfield(L, stack_pos_image_component, "x");
			icomponent->x = lua_tonumber(L,  -1);
			lua_pop(L, 1);
			
			lua_getfield(L, stack_pos_image_component, "y");
			icomponent->y = lua_tonumber(L,  -1);
			lua_pop(L, 1);
			
			lua_getfield(L, stack_pos_image_component, "scale");
			icomponent->scale = lua_tonumber(L,  -1);
			lua_pop(L, 1);
			
			lua_getfield(L, stack_pos_image_component, "rotation");
			icomponent->rotation = lua_tonumber(L,  -1);
			lua_pop(L, 1);
			
			lua_getfield(L, stack_pos_image_component, "width");
			icomponent->width = lua_tointeger(L,  -1);
			lua_pop(L, 1);
			
			lua_getfield(L, stack_pos_image_component, "height");
			icomponent->height = lua_tointeger(L,  -1);
			lua_pop(L, 1);
			
			icomponent->animation_time = SDL_GetTicks();
			icomponent->animations = array_create();
			icomponent->animation_selected = 0;
			
			lua_getfield(L, stack_pos_image_component, "animations");
			int stack_pos_animation_table = lua_gettop(L);
			if(lua_istable(L, stack_pos_animation_table))
			{
				lua_pushnil(L);
				while(lua_next(L, stack_pos_animation_table))
				{
					int stack_pos_animation = lua_gettop(L);
					if(lua_istable(L, stack_pos_animation))
					{
						Animation* animation = malloc(sizeof(Animation));
						if(animation == NULL)
						{
							error_popup("Memory allocation failed (load_entity)");
							return NULL;
						}
						animation->frame = 0;
						animation->s_rects = array_create();
						
						lua_getfield(L, stack_pos_animation, "delay");
						animation->delay = lua_tointeger(L, -1);
						lua_pop(L, 1);
						
						for(int i = 1; 1; i++)
						{
							lua_pushnumber(L, stack_pos_animation_pos);
							lua_gettable(L, stack_pos_animation_pos);
							if(lua_isnil(L, -1))
							{
								break;
							}
							
							SDL_Rect* s_rect = malloc(sizeof(SDL_Rect));
							if(s_rect == NULL)
							{
								error_popup("Memory allocation failed (load_entity)");
								return NULL;
							}
								
							s_rect->w = icomponent->width;
							s_rect->h = icomponent->height;
							s_rect->x = (lua_tointeger(L, -1) - 1) * s_rect->w; 
							lua_pop(L, 1);
								
							lua_pushnumber(L, 2);
							lua_gettable(L, stack_pos_animation_pos);
							s_rect->y = (lua_tointeger(L, -1) - 1) * s_rect->h; 
							lua_pop(L, 1);
								
							array_push(animation->s_rects, array_getlength(animation->s_rects), s_rect);
						}
						
						array_push(icomponent->animations, 0, animation);
					}
					lua_pop(L, 1);
				}
				lua_pop(L, 1);
			}
			else
			{
				Animation* animation = malloc(sizeof(Animation));
				if(animation == NULL)
				{
					error_popup("Memory allocation failed (load_entity)");
					return NULL;
				}
				animation->frame = 0;
				animation->s_rects = array_create();
				animation->delay = 0;
				
				SDL_Rect* s_rect = malloc(sizeof(SDL_Rect));
				if(s_rect == NULL)
				{
					error_popup("Memory allocation failed (load_entity)");
					return NULL;
				}
				
				s_rect->x = 0;
				s_rect->y = 0;
				s_rect->w = icomponent->width;
				s_rect->h = icomponent->height;
				
				array_push(animation->s_rects, 0, s_rect);
				array_push(icomponent->animations, 0, animation);
			}
			lua_pop(L, 1);
		}
		lua_pop(L, 1);
		
		lua_getfield(L, 1, "text_component");
		if(lua_istable(L, 2))
		{
			//Do stuff
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	
	return entity;
}
*/
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

	Entity* player = entity_create("player");
	entity_addcomponent(player, COMPONENT_IMAGE, icomponent_create(program.renderer, "../../res/images/TP_1.0_SpriteSheet.png", 250.0, 250.0, 32, 32, 6.0, 0.0));
	if(player == NULL)
	{
		error_popup("ERRR");
	}

	array_push(program.entities, 0, player);

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
		Image_Component* icomponent = entity_getcomponent(entity, COMPONENT_IMAGE);
		if(icomponent != NULL)
		{
			icomponent_render(icomponent, program->renderer);
		}
		
		Text_Component* tcomponent = entity_getcomponent(entity, COMPONENT_TEXT);
		if(tcomponent != NULL)
		{
			printf("text indeed\n");
		}
	}
	
	SDL_RenderPresent(program->renderer);
	return 0;
}
