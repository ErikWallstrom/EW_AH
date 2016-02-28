#include "Dimension.h"
#include "Error.h"
#include <stdlib.h>
#include <assert.h>

Component_Type DIMENSION_COMPONENT = "Dimension";
struct Dimension
{
	Component info;
	int width, height;
};

Dimension* Dimension_create(int width, int height)
{
	Dimension* self = malloc(sizeof(Dimension));
	if(!self)
		error(ERROR_ALLOC);

	self->info.type = String_create(DIMENSION_COMPONENT);
	self->width = width;
	self->height = height;
	return self;
}

void Dimension_destroy(Dimension** d_component)
{
	assert(d_component && (*d_component));
	free((*d_component));
	(*d_component) = NULL;
}

int Dimension_get_width(const Dimension* self)
{
	assert(self);
	return self->width;
}

int Dimension_get_height(const Dimension* self)
{
	assert(self);
	return self->height;
}

void Dimension_set_width(Dimension* self,
								   int width)
{
	assert(self);
	self->width = width;
}

void Dimension_set_height(Dimension* self,
									int height)
{
	assert(self);
	self->height = height;
}
