#ifndef IMAGE_COMPONENT_H
#define IMAGE_COMPONENT_H

#include "Component.h"
#include <SDL_2/SDL_image.h>
extern Component_Type IMAGE_COMPONENT;
typedef struct Image_Component Image_Component;

Image_Component* Image_Component_create(SDL_Renderer* renderer,
										const char* file);
void Image_Component_destroy(Image_Component** i_component);

SDL_Texture* Image_Component_get_texture(const Image_Component* self);
const char* Image_Component_get_file(const Image_Component* self);

#endif