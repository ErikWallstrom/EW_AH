#include "Position_Component.h"
#include "Error.h"
#include <stdlib.h>
#include <assert.h>

Component_Type POSITION_COMPONENT = "position_component";
struct Position_Component
{
	Component info;
	double x, y;
};

Position_Component* Position_Component_create(double x, double y)
{
	Position_Component* self = malloc(sizeof(Position_Component));
	if(!self)
		error(ERROR_ALLOC);
	
	self->info.type = String_create(POSITION_COMPONENT);
	self->x = x;
	self->y = y;
	return self;
}

void Position_Component_destroy(Position_Component** p_component)
{
	assert(p_component && (*p_component));
	String_destroy(&(*p_component)->info.type);
	free((*p_component));
	(*p_component) = NULL;
}

double Position_Component_get_x(const Position_Component* self)
{
	assert(self);
	return self->x;
}

double Position_Component_get_y(const Position_Component* self)
{
	assert(self);
	return self->y;
}


void Position_Component_set_x(Position_Component* self, double x)
{
	assert(self);
	self->x = x;
}

void Position_Component_set_y(Position_Component* self, double y)
{
	assert(self);
	self->y = y;
}
