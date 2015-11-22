#ifndef ENTITY_H
#define ENTITY_H

	#include "../include/SDL2/SDL_image.h"
	#include "../include/Lua_5.3/lua.h"
	#include "Array.h"

	typedef struct Entity Entity;
	typedef struct Graphics_Component Graphics_Component;
	
	typedef enum
	{
		GRAPHICS
		
	} Component_Type;
	
	struct Graphics_Component
	{
		SDL_Texture* texture;
		double x, y;
		int width, height;
		
		int animation_selected;
		int animation_delay;
		int animation_time;
		Array* images;
	};
	
	Entity* entity_create		(lua_State* script, SDL_Renderer* renderer, const char* name);
	void 	entity_destroy		(Entity* entity);
	void* 	entity_getcomponent	(Entity* entity, Component_Type component);

#endif