#include "Main.h"

int main(void)
{
	if(initialize_libraries())
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
	
	array_push(program.entities, 0, entity_create(program.script, program.renderer, "player"));
	
	int done = 0;
	while(!done)
	{
		render(&program);
		done = process_events(&program);
	}

	lua_close(program.script);
	SDL_DestroyWindow(program.window);
	SDL_DestroyRenderer(program.renderer);
	array_destroy(program.entities);
	
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
	SDL_SetRenderDrawColor(program->renderer, 0, 0, 255, 255);
	SDL_RenderClear(program->renderer);
	
	for(int i = 0; i < array_getlength(program->entities); i++)
	{
		Entity* entity = array_getvalue(program->entities, i);
		Graphics_Component* gcomponent = entity_getcomponent(entity, GRAPHICS);
		 
		SDL_Rect dRect = {
			 (int)gcomponent->x, (int)gcomponent->y,
			 gcomponent->width, gcomponent->height
		};
		
		if(gcomponent->images != NULL)
		{
			if(SDL_GetTicks() - gcomponent->animation_delay > gcomponent->animation_time && 
			   SDL_GetTicks() > 1000)
			{
				gcomponent->animation_selected++;
				if(gcomponent->animation_selected > array_getlength(gcomponent->images) - 1)
				{
					gcomponent->animation_selected = 0;
				}
				
				gcomponent->animation_time = SDL_GetTicks();
			}
			
			SDL_Rect* sRect = array_getvalue(gcomponent->images, gcomponent->animation_selected);
			SDL_RenderCopy(program->renderer, gcomponent->texture, sRect, &dRect);
		}
		else
		{
			SDL_RenderCopy(program->renderer, gcomponent->texture, NULL, &dRect);
		}
	}
	
	SDL_RenderPresent(program->renderer);
	return 0;
}
