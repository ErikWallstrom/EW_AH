#include "Components.h"
#include "Array.h"
#include "Error.h"

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/SDL2/SDL_image.h"

#include <math.h>
#include <stdlib.h>

struct Animation
{
	Array* s_rects;
	int frame;
	unsigned int time;
	unsigned int delay;
};

struct Image_Component
{
	SDL_Texture* texture;
	int width, height;
	double x, y, rotation, scale;	
	
	Array* animations;
	int animation_selected;
};

struct Text_Component
{
	SDL_Texture* texture;
	TTF_Font* font;
	char* text;
	int width, height;
	double x, y, rotation, scale;
		
	Array* animations;
	int animation_selected;	
};

Image_Component* icomponent_create(
	SDL_Renderer* renderer, const char* file, 
	double x, double y, 
	int width, int height,
	double scale, double rotation					   
)
{
	Image_Component* icomponent = malloc(sizeof(Image_Component));
	if(icomponent == NULL)
	{
		error_popup("Memory allocation error");
		return NULL;
	}
	
	icomponent->texture = IMG_LoadTexture(renderer, file);
	if(icomponent->texture == NULL)
	{
		error_popup(IMG_GetError());
		return NULL;
	}
	
	icomponent->x = x;
	icomponent->y = y;
	icomponent->scale = scale;
	icomponent->width = width;
	icomponent->height = height;
	icomponent->rotation = rotation;
	icomponent->animations = NULL;
	icomponent->animation_selected = 0;
	
	return icomponent;
}

void icomponent_destroy(Image_Component** icomponent)
{
	if(icomponent != NULL)
	{
		if((*icomponent) != NULL)
		{
			if((*icomponent)->texture != NULL)
			{
				SDL_DestroyTexture((*icomponent)->texture);
			}
			
			if((*icomponent)->animations != NULL)
			{
				//TODO: Clean up memory in array
				array_destroy(&(*icomponent)->animations);
			}
			
			free((*icomponent));
		}
	}
	
	(*icomponent) = NULL;
}

int icomponent_render(Image_Component* icomponent, SDL_Renderer* renderer)
{
	if(icomponent != NULL && renderer != NULL)
	{
		//TODO: Animation
		SDL_Rect d_rect = {
			(int)round(icomponent->x),
			(int)round(icomponent->y),
			icomponent->width,
			icomponent->height
		};
		SDL_RenderCopyEx(renderer, icomponent->texture, NULL, &d_rect, icomponent->rotation, NULL, SDL_FLIP_NONE);
	}
	
	return 0;
}
