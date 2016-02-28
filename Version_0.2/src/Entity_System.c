#include "Entity_System.h"
#include "Dimension.h"
#include "Position.h"
#include "Image.h"
#include "Entity.h"
#include "Array.h"
#include "Error.h"

#include <Lua_5.3/lauxlib.h>
#include <Lua_5.3/lualib.h>
#include <SDL_2/SDL.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

struct Entity_System
{
	Array* entities;
	lua_State* script;
	SDL_Renderer* renderer;
};

/* Lua accessible functions */
int lua_create_entity(lua_State* L)
{
	Entity_System* self = luaL_checkudata(L, 1, "Entity_System");
	luaL_checktype(L, 2, LUA_TTABLE);
	
	const char* name;
	lua_getfield(L, 2, "name");
	if(lua_isstring(L, -1))
		name = lua_tolstring(L, -1, NULL);
	else
		name = "entity";
	lua_pop(L, 1);
	
	Entity* entity = Entity_create(name);
	lua_getfield(L, 2, "dimension");
	if(lua_istable(L, -1))
	{
		int dimension_pos = lua_gettop(L);
		lua_getfield(L, dimension_pos, "width");
		lua_getfield(L, dimension_pos, "height");
		if(lua_isinteger(L, -1) && lua_isinteger(L, -2))
		{
			Dimension* d = Dimension_create(
				lua_tointeger(L, -2), lua_tointeger(L, -1));
			Entity_add(entity, d);
		}
		lua_pop(L, 2);
	}
	lua_pop(L, 1);
	
	lua_getfield(L, 2, "position");
	if(lua_istable(L, -1))
	{
		int position_pos = lua_gettop(L);
		lua_getfield(L, position_pos, "x");
		lua_getfield(L, position_pos, "y");
		if(lua_isnumber(L, -1) && lua_isnumber(L, -2))
		{
			Position* p = Position_create(
				lua_tonumber(L, -2), lua_tonumber(L, -1));
			Entity_add(entity, p);
		}
		lua_pop(L, 2);
	}
	lua_pop(L, 1);
	
	lua_getfield(L, 2, "image");
	if(lua_istable(L, -1))
	{
		int image_pos = lua_gettop(L);
		lua_getfield(L, image_pos, "src");
		if(lua_isstring(L, -1))
		{
			Image* i = Image_create(
				self->renderer, lua_tostring(L, -1));
			if(i)
			{
				Entity_add(entity, i);
			}
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	Entity_System_add(self, entity);
	return 0;
}

Entity_System* Entity_System_create(const Window* window)
{
	assert(window);
	Entity_System* self = malloc(sizeof(Entity_System));
	self->entities = Array_create();
	self->renderer = Window_get_renderer(window);
	
	self->script = luaL_newstate();
	if(!self->script)
		error(ERROR_ALLOC);
	luaL_openlibs(self->script);
	
	//If metatable for engine does not already exist
	if(luaL_newmetatable(self->script, "Entity_System"))
	{
		int mt = lua_gettop(self->script);
		const luaL_Reg methods[] = {
			{"create", lua_create_entity},
			{NULL, NULL}
		};
		luaL_newlib(self->script, methods);
		lua_setfield(self->script, mt, "__index");
	}
	lua_pop(self->script, 1);
	Entity_System* lua_self = lua_newuserdata(
		self->script, sizeof(Entity_System));
	memcpy(lua_self, self, sizeof(Entity_System));
	luaL_setmetatable(self->script, "Entity_System");
	lua_setglobal(self->script, "engine");
	return self;
}

void Entity_System_destroy(Entity_System** e_system)
{
	assert(e_system && (*e_system));
	lua_close((*e_system)->script);
	Array_destroy(&(*e_system)->entities);
	free((*e_system));
	(*e_system) = NULL;
}

bool Entity_System_add(Entity_System* self, Entity* entity)
{
	assert(self && entity);
	foreach(i, self->entities)
	{
		Entity* e = Array_get(self->entities, i);
		if(!strcmp(Entity_get_name(entity), Entity_get_name(e)))
		{
			return false;
		}
	}
	
	Array_insert(self->entities, 0, entity);
	return true;
}

void Entity_System_load(Entity_System* self, const char* file)
{
	assert(self && file);
	if(luaL_dofile(self->script, file))
		error(lua_tostring(self->script, -1));
}

/* Private functions */
void Rendering_System(SDL_Renderer* renderer, Entity* e)
{
	if(Entity_has(e, DIMENSION_COMPONENT) &&
		Entity_has(e, POSITION_COMPONENT) &&
		Entity_has(e, IMAGE_COMPONENT))
	{
		Dimension* d = Entity_get(e, DIMENSION_COMPONENT);
		Position* p = Entity_get(e, POSITION_COMPONENT);
		Image* i = Entity_get(e, IMAGE_COMPONENT);
		
		SDL_Rect d_rect = {
			.x = round(Position_get_x(p) -
				Dimension_get_width(d) / 2.0),
			.y = round(Position_get_y(p) - 
				Dimension_get_height(d) / 2.0),
			.w = Dimension_get_width(d),
			.h = Dimension_get_height(d)
		};
		
		SDL_RenderCopy(renderer, Image_get_texture(i),
			NULL, &d_rect);
	}
}

void Entity_System_start(Entity_System* self)
{
	assert(self);
	bool done = false;
	while(!done)
	{
		SDL_RenderClear(self->renderer);
		foreach(i, self->entities)
		{
			Entity* e = Array_get(self->entities, i);
			Rendering_System(self->renderer, e);
		}
		SDL_RenderPresent(self->renderer);
	}
}
