#include "Script.h"
	
//Standard Library
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

//SDL2
#include "../include/SDL2/SDL.h"

//Lua 5.3
#include "../include/Lua_5.3/lua.h"
#include "../include/Lua_5.3/lualib.h"
#include "../include/Lua_5.3/lauxlib.h"

const char* script_getstring(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	memcpy(buffer, script, strlen(script));
	memcpy(buffer + strlen(script), variable_name, strlen(variable_name) + 1);
	
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
	return lua_tostring(L, -1);
}
	
double script_getnumber(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	memcpy(buffer, script, strlen(script));
	memcpy(buffer + strlen(script), variable_name, strlen(variable_name) + 1);
	
	if(luaL_dostring(L, script)) //If error
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
	return lua_tonumber(L, -1);
}
	
int script_getinteger(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	memcpy(buffer, script, strlen(script));
	memcpy(buffer + strlen(script), variable_name, strlen(variable_name) + 1);
	
	if(luaL_dostring(L, script)) //If error
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
	return lua_tointeger(L, -1);
}
	
int script_getboolean(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	memcpy(buffer, script, strlen(script));
	memcpy(buffer + strlen(script), variable_name, strlen(variable_name) + 1);
	
	if(luaL_dostring(L, script)) //If error
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
	return lua_toboolean(L, -1);
}

int	script_getnil(lua_State* L, const char* variable_name)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	memcpy(buffer, script, strlen(script));
	memcpy(buffer + strlen(script), variable_name, strlen(variable_name) + 1);
	
	if(luaL_dostring(L, script)) //If error
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
	if(lua_isnil(L, -1))
	{
		return 1;
	}
	
	return 0;
}
	
int script_callfunction(lua_State* L, const char* function_name,
						int num_returns, const char* parameters, ...)
{
	const char script[] = "__getvariable=";
	char* buffer = malloc(strlen(script) + strlen(variable_name) + 1);
	memcpy(buffer, script, strlen(script));
	memcpy(buffer + strlen(script), variable_name, strlen(variable_name) + 1);
	
	if(luaL_dostring(L, script)) //If error
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
		return 1;
	}
	
	return 0;
}

