#ifndef SCRIPT_H
#define SCRIPT_H

	typedef struct lua_State lua_State;
	
	const char* script_getstring	(lua_State* L, const char* variable_name);
	double 		script_getnumber	(lua_State* L, const char* variable_name);
	int 		script_getinteger	(lua_State* L, const char* variable_name);
	int 		script_getboolean	(lua_State* L, const char* variable_name);
	int 		script_callfunction (lua_State* L, const char* function_name,
									 int num_returns, const char* parameters, ...);

#endif