#include <Lua_5.3/lauxlib.h>
#include <Lua_5.3/lualib.h>

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	lua_State* script = luaL_newstate();
	if(!script)
	{
		return EXIT_FAILURE;
	}
	
	luaL_openlibs(script);
	if(luaL_dofile(script, "../../res/scripts/main.lua"))
	{
		printf("Error: %s\n", 
			lua_tolstring(script, -1, NULL)
		);
		return EXIT_FAILURE;
	}
	
	lua_close(script);
}
