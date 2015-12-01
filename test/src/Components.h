#ifndef IMAGE_COMPONENT_H
#define IMAGE_COMPONENT_H

	#include "Array.h"
	#include "../include/SDL2/SDL.h"
	#include "../include/SDL2/SDL_ttf.h"
	#include "../include/Lua_5.3/lauxlib.h"

	typedef struct
	{
		Array* s_rects;
		int frame;
		unsigned int delay;
		
	} Animation;

	typedef struct
	{
		SDL_Texture* texture;
		int width, height;
		double x, y, rotation, scale;
		
		Array* animations;
		int animation_selected;
		unsigned int animation_time;
		
	} Image_Component;

	typedef struct
	{
		SDL_Texture* texture;
		TTF_Font* font;
		char* text;
		int width, height;
		double x, y, rotation, scale;
		
		Array* animations;
		int animation_time;
		int animation_selected;
		
	} Text_Component;
	
	Image_Component* create_icomponent(const char* file, double x, double y, 
									   double rotation, double scale, 
									   int width, int height
									   
	)
	{
		
	}
	
#endif
