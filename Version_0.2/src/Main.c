#include <stdlib.h>
#include <stdio.h>

#include "Entity_System.h"
#include "Libraries.h"
#include "Window.h"

#undef main
int main(void)
{
	Libraries_initialize();

	Window* window = Window_create("Game Window", 800, 600);
	Entity_System* e = Entity_System_create(window);
	Entity_System_load(e, "../../res/scripts/main.lua");
	
	Entity_System_start(e);
	
	getchar();
	Entity_System_destroy(&e);
	Window_destroy(&window);
	Libraries_terminate();
}
