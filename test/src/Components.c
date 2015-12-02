#include "Components.h"
#include "Array.h"
#include "Error.h"

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/SDL2/SDL_image.h"

#include <math.h>
#include <stdlib.h>

typedef struct
{
	SDL_Rect* s_rects;
	int total_frames;
	int frame_selected;
	unsigned int time;
	unsigned int delay;
	
} Animation;

struct Graphics_Component
{
	SDL_Texture* texture;
	int width, height;
	double x, y, rotation, scale;	
	
	Array* animations;
	int animation_selected;
};

Graphics_Component* gcomponent_create(
	SDL_Renderer* renderer, const char* file, 
	double x, double y, 
	int width, int height,
	double scale, double rotation					   
)
{
	Graphics_Component* gcomponent = malloc(sizeof(Graphics_Component));
	if(gcomponent == NULL)
	{
		error_popup("Memory allocation error");
		return NULL;
	}
	
	gcomponent->texture = IMG_LoadTexture(renderer, file);
	if(gcomponent->texture == NULL)
	{
		error_popup(IMG_GetError());
		return NULL;
	}
	
	gcomponent->x = x;
	gcomponent->y = y;
	gcomponent->scale = scale;
	gcomponent->width = width;
	gcomponent->height = height;
	gcomponent->rotation = rotation;
	gcomponent->animation_selected = 0;
	gcomponent->animations = array_create();
	
	return gcomponent;
}

void gcomponent_destroy(Graphics_Component** gcomponent)
{
	if(gcomponent != NULL)
	{
		if((*gcomponent) != NULL)
		{
			if((*gcomponent)->texture != NULL)
			{
				SDL_DestroyTexture((*gcomponent)->texture);
			}
			
			if((*gcomponent)->animations != NULL)
			{
				//TODO: Clean up memory in array
				array_destroy(&(*gcomponent)->animations);
			}
			
			free((*gcomponent));
		}
	}
	
	(*gcomponent) = NULL;
}

int gcomponent_render(Graphics_Component* gcomponent, SDL_Renderer* renderer)
{
	if(gcomponent != NULL && renderer != NULL)
	{
		SDL_Rect d_rect = {
			(int)round(gcomponent->x),
			(int)round(gcomponent->y),
			(int)round(gcomponent->width * gcomponent->scale),
			(int)round(gcomponent->height * gcomponent->scale)
		};
		
		if(array_getlength(gcomponent->animations) > 0)
		{
			Animation* animation = array_getvalue(gcomponent->animations, gcomponent->animation_selected);
			SDL_Rect s_rect = animation->s_rects[animation->frame_selected];
			if(SDL_GetTicks() - animation->time > animation->delay)
			{
				animation->time = SDL_GetTicks();
				animation->frame_selected++;
				if(animation->frame_selected >= animation->total_frames)
				{
					animation->frame_selected = 0;
				}
			}
			
			SDL_RenderCopyEx(renderer, gcomponent->texture, &s_rect, &d_rect, gcomponent->rotation, NULL, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopyEx(renderer, gcomponent->texture, NULL, &d_rect, gcomponent->rotation, NULL, SDL_FLIP_NONE);
		}
		
		return 1;
	}
	
	return 0;
}

int gcomponent_addanimation(Graphics_Component* gcomponent, int total_frames, SDL_Rect* frames, unsigned int delay)
{
	Animation* animation = malloc(sizeof(Animation));
	if(animation == NULL)
	{
		error_popup("Memory allocation error");
		return 0;
	}
	
	animation->total_frames = total_frames;
	animation->frame_selected = 0;
	animation->time = SDL_GetTicks();
	animation->delay = delay;
	
	animation->s_rects = malloc(sizeof(SDL_Rect) * total_frames);
	if(animation->s_rects == NULL)
	{
		error_popup("Memory allocation error");
		return 0;
	}
	
	for(int i = 0; i < total_frames; i++)
	{
		animation->s_rects[i].x = frames[i].x;
		animation->s_rects[i].y = frames[i].y;
		animation->s_rects[i].w = gcomponent->width;
		animation->s_rects[i].h = gcomponent->height;
	}

	array_push(gcomponent->animations, array_getlength(gcomponent->animations), animation);
	return 1;
}

//int gcomponent_removeanimation(...)
