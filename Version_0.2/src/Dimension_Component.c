#include "Dimension_Component.h"
#include "Error.h"
#include <stdlib.h>
#include <assert.h>

Component_Type DIMENSION_COMPONENT = "dimension_component";
struct Dimension_Component
{
	Component info;
	int width, height;
};

Dimension_Component* Dimension_Component_create(int width, 
												int height)
{
	Dimension_Component* self = malloc(sizeof(Dimension_Component));
	if(!self)
		error(ERROR_ALLOC);
	
	self->info.type = String_create(DIMENSION_COMPONENT);
	self->width = width;
	self->height = height;
	return self;
}

void Dimension_Component_destroy(Dimension_Component** d_component)
{
	assert(d_component && (*d_component));
	free((*d_component));
	(*d_component) = NULL;
}

int Dimension_Component_get_width(const Dimension_Component* self)
{
	assert(self);
	return self->width;
}

int Dimension_Component_get_height(const Dimension_Component* self)
{
	assert(self);
	return self->height;
}

void Dimension_Component_set_width(Dimension_Component* self, 
								   int width)
{
	assert(self);
	self->width = width;
}

void Dimension_Component_set_height(Dimension_Component* self, 
									int height)
{
	assert(self);
	self->height = height;
}
