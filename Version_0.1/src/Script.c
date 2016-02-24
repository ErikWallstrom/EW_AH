#include "Script.h"
#include "Error.h"
#include "Entity.h"
#include "Event_Component.h"
#include "Graphics_Component.h"

//Standard Library
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

//SDL2
#include "../include/SDL2/SDL_image.h" //For SDL_ShowSimpleMessageBox

//Lua 5.3
#include "../include/Lua_5.3/lualib.h"
#include "../include/Lua_5.3/lauxlib.h"

lua_State* script_initialize(const char* file)
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

double script_getnumber(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	strcpy(buffer, script);
	strcpy(buffer + strlen(script), variable_name);
	
	if(luaL_dostring(L, buffer)) //If error
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return 0.0;
	}
	lua_getglobal( L, "__getvariable" );  
	if(!lua_isnumber(L, -1))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_WARNING, 
			"Warning", 
			"Lua variable is not a number", 
			NULL
		);
		lua_pop(L, 1);
		return 0.0;
	}
	
	double val = lua_tonumber(L, -1);
	lua_pop(L, 1);
	
	return val;
}

const char* script_getstring(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	strcpy(buffer, script);
	strcpy(buffer + strlen(script), variable_name);
	
	if(luaL_dostring(L, buffer)) //If error
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return NULL;
	}
	lua_getglobal( L, "__getvariable" );  
	if(!lua_isstring(L, -1))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_WARNING, 
			"Warning", 
			"Lua variable is not a string", 
			NULL
		);
		lua_pop(L, 1);
		return NULL;
	}
	
	const char* val = lua_tostring(L, -1);
	lua_pop(L, 1);
	return val;
}
	
int script_getinteger(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	strcpy(buffer, script);
	strcpy(buffer + strlen(script), variable_name);
	
	if(luaL_dostring(L, buffer)) //If error
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return 0;
	}
	lua_getglobal( L, "__getvariable" );  
	if(!lua_isinteger(L, -1))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_WARNING, 
			"Warning", 
			"Lua variable is not an integer", 
			NULL
		);
		lua_pop(L, 1);
		return 0;
	}
	
	int val = lua_tointeger(L, -1);
	lua_pop(L, 1);
	return val;
}
	
int script_getboolean(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	strcpy(buffer, script);
	strcpy(buffer + strlen(script), variable_name);
	
	if(luaL_dostring(L, buffer)) //If error
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return 0;
	}
	lua_getglobal( L, "__getvariable" );  
	if(!lua_isnumber(L, -1))
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_WARNING, 
			"Warning", 
			"Lua variable is not a boolean", 
			NULL
		);
		lua_pop(L, 1);
		return 0;
	}
	
	int val = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return val;
}

int	script_getnil(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	strcpy(buffer, script);
	strcpy(buffer + strlen(script), variable_name);
	
	if(luaL_dostring(L, buffer)) //If error
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return 1;
	}
	lua_getglobal( L, "__getvariable" );  
	if(lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		return 1;
	}
	
	lua_pop(L, 1);
	return 0;
}
	
int script_callfunction(lua_State* L, const char* variable_name,
						int num_returns, const char* parameters, ...)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	strcpy(buffer, script);
	strcpy(buffer + strlen(script), variable_name);
	
	if(luaL_dostring(L, buffer)) //If error
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		return 1;
	}
	lua_getglobal( L, "__getvariable" );
	
	int num_params = 0;
	if(parameters != NULL)
	{
		va_list args;
		va_start(args, parameters);
		while(*parameters != '\0')
		{
			switch(*parameters)
			{
				case 'i':
					lua_pushinteger(L, (int)va_arg(args, int));
					num_params++;
				break;
					
				case 'f':
					lua_pushnumber(L, (double)va_arg(args, double));
					num_params++;
				break;
					
				case 's':
					lua_pushstring(L, (const char*)va_arg(args, const char*));
					num_params++;
				break;
			}
				
			parameters++;
		}
		va_end(args);
	}
	
	if(lua_pcall(L, num_params, num_returns, 0)) //If error
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			lua_tostring(L, -1), 
			NULL
		);
		lua_pop(L, 1);
		return 1;
	}
	
	lua_pop(L, 1);
	return 0;
}

Entity* script_loadentity(lua_State* L, const char* entity_name, SDL_Renderer* renderer)
{
	Entity* entity = entity_create(entity_name);
	lua_getglobal(L, entity_name);
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
			double x = lua_tonumber(L, -1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "y");
			double y = lua_tonumber(L, -1);
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
								lua_gettable(L, -2);
								frames[total_frames - 1].y = (lua_tointeger(L, -1) - 1) * height;
								lua_pop(L, 1);
								
								frames[total_frames - 1].w = width;
								frames[total_frames - 1].h = height;
							}
						}
						lua_pop(L, 1);
					}
					gcomponent_createanimations(gcomponent, total_frames, frames, lua_tostring(L, -2), delay);
					free(frames);
					lua_pop(L, 1);
				}
				lua_pop(L, 1);
			}
			lua_pop(L, 1);
			entity_addcomponent(entity, COMPONENT_GRAPHICS, gcomponent);
		}
		
		lua_getfield(L, -1, "event_component");
		if(lua_istable(L, -1))
		{
			entity_addcomponent(entity, COMPONENT_EVENT, ecomponent_create());
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	
	return entity;
}

//*********************************************************************************************
//Lua accessable functions

int script_lua_selectanimation(lua_State* L)
{
	//1 is table
	const char* name = lua_tostring(L, 2);
	
	lua_getfield(L, 1, "pointer");
	Graphics_Component* gcomponent = lua_touserdata(L, -1);
	gcomponent_selectanimation(gcomponent, name);
	
	return 0;
}

//*********************************************************************************************

int script_pushentity(lua_State* L, Entity* entity)
{
	lua_createtable(L, 0, 7); //num of number key, num of string key
	int table_pos = lua_gettop(L);
	
	Graphics_Component* gcomponent = entity_getcomponent(entity, COMPONENT_GRAPHICS);
	if(gcomponent != NULL)
	{
		lua_pushliteral(L, "x");
		lua_pushnumber(L, gcomponent_getx(gcomponent));
		lua_settable(L, table_pos);
		
		lua_pushliteral(L, "y");
		lua_pushnumber(L, gcomponent_gety(gcomponent));
		lua_settable(L, table_pos);
		
		lua_pushliteral(L, "scale");
		lua_pushnumber(L, gcomponent_getscale(gcomponent));
		lua_settable(L, table_pos);
		
		lua_pushliteral(L, "rotation");
		lua_pushnumber(L, gcomponent_getrotation(gcomponent));
		lua_settable(L, table_pos);
		
		lua_pushliteral(L, "pointer");
		lua_pushlightuserdata(L, gcomponent);
		lua_settable(L, table_pos);
		
		lua_pushliteral(L, "set_animation");
		lua_pushcfunction(L, script_lua_selectanimation);
		lua_settable(L, table_pos);
	}
	
	return 1; //TODO: Add error handeling
}

int script_popentity(lua_State* L)
{
	int table_pos = lua_gettop(L);
	
	lua_getfield(L, table_pos, "pointer");
	Graphics_Component* gcomponent = lua_touserdata(L, -1);
	lua_pop(L, 1);
	
	lua_getfield(L, table_pos, "x");
	gcomponent_setx(gcomponent, lua_tonumber(L, -1));
	lua_pop(L, 1);
	
	lua_getfield(L, table_pos, "y");
	gcomponent_sety(gcomponent, lua_tonumber(L, -1));
	lua_pop(L, 1);
	
	lua_getfield(L, table_pos, "scale");
	gcomponent_setscale(gcomponent, lua_tonumber(L, -1));
	lua_pop(L, 1);
	
	lua_getfield(L, table_pos, "rotation");
	gcomponent_setrotation(gcomponent, lua_tonumber(L, -1));
	lua_pop(L, 1);
	
	lua_pop(L, 1);
	return 1; //TODO: Add error handeling
}
