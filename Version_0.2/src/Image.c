#include "Image.h"
#include "Error.h"
#include <stdlib.h>
#include <assert.h>

Component_Type IMAGE_COMPONENT = "Image";
struct Image
{
	Component info;
	SDL_Texture* texture;
	String* file;
};

Image* Image_create(SDL_Renderer* renderer, const char* file)
{
	assert(renderer && file);
	SDL_Texture* texture = IMG_LoadTexture(renderer, file);
	if(!texture)
		return NULL;
	
	Image* self = malloc(sizeof(Image));
	if(!self)
		error(ERROR_ALLOC);
	
	self->info.type = String_create(IMAGE_COMPONENT);
	self->texture = texture;
	self->file = String_create(file);
	return self;
}

void Image_destroy(Image** i_component)
{
	assert(i_component && (*i_component));
	SDL_DestroyTexture((*i_component)->texture);
	String_destroy(&(*i_component)->file);
	free((*i_component));
}

SDL_Texture* Image_get_texture(const Image* self)
{
	assert(self);
	return self->texture;
}

const char* Image_get_file(const Image* self)
{
	assert(self);
	return String_get(self->file);
}
