#ifndef SCRIPTAUX_H
#define SCRIPTAUX_H

	//Lua 5.3
	#include "../include/Lua_5.3/lua.h"
	#include "../include/Lua_5.3/lualib.h"
	#include "../include/Lua_5.3/lauxlib.h"
	
	const char* script_getstring	(lua_State* L, const char* variable_name);
	int 		script_getinteger	(lua_State* L, const char* variable_name);
	double 		script_getnumber	(lua_State* L, const char* variable_name);
	int 		script_getboolean	(lua_State* L, const char* variable_name);
	
	const char* script_getstring(lua_State* L, const char* variable_name)
	{
		char script[32] = "__getvariable=";
		strcat(script, variable_name);
		luaL_dostring(L, script);
		lua_getglobal( L, "__getvariable" );  
	
		const char* string = lua_tostring(L, -1);
		lua_pop(L, 1);
		
		return string;
	}
	
	int script_getinteger(lua_State* L, const char* variable_name)
	{
		char script[32] = "__getvariable=";
		strcat(script, variable_name);
		luaL_dostring(L, script);
		lua_getglobal( L, "__getvariable" );  
	
		int integer = lua_tointeger(L, -1);
		lua_pop(L, 1);
		
		return integer;
	}
	
	double script_getnumber(lua_State* L, const char* variable_name)
	{
		char script[32] = "__getvariable=";
		strcat(script, variable_name);
		luaL_dostring(L, script);
		lua_getglobal( L, "__getvariable" );  
	
		double number = lua_tonumber(L, -1);
		lua_pop(L, 1);
		
		return number;
	}
	
	int script_getboolean(lua_State* L, const char* variable_name)
	{
		char script[32] = "__getvariable=";
		strcat(script, variable_name);
		luaL_dostring(L, script);
		lua_getglobal( L, "__getvariable" );  
	
		int boolean = lua_toboolean(L, -1);
		lua_pop(L, 1);
		
		return boolean;
	}

#endif