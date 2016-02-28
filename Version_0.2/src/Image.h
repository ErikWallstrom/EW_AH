#ifndef Image_H
#define Image_H

#include "Component.h"
#include <SDL_2/SDL_image.h>
extern Component_Type IMAGE_COMPONENT;
typedef struct Image Image;

Image* Image_create(SDL_Renderer* renderer,
										const char* file);
void Image_destroy(Image** i_component);

SDL_Texture* Image_get_texture(const Image* self);
const char* Image_get_file(const Image* self);

#endif