#ifndef SCRIPT_H
#define SCRIPT_H
	
	typedef struct Entity Entity;
	typedef struct lua_State lua_State;
	typedef struct SDL_Renderer SDL_Renderer;
	
	lua_State*  script_initialize	(const char* file);
	double 		script_getnumber	(lua_State* L, const char* variable_name);
	const char*	script_getstring	(lua_State* L, const char* variable_name);
	int 		script_getinteger	(lua_State* L, const char* variable_name);
	int 		script_getboolean	(lua_State* L, const char* variable_name);
	int			script_getnil		(lua_State* L, const char* variable_name);
	int 		script_callfunction (lua_State* L, const char* function_name,
									 int num_returns, const char* parameters, ...);
									 
	Entity*		script_loadentity	(lua_State* L, const char* entity_name, 
									 SDL_Renderer* renderer);
	int 		script_pushentity	(lua_State* L, Entity* entity);
	int 		script_popentity	(lua_State* L);

#endif
