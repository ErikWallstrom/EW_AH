#include "Position.h"
#include "Error.h"
#include <stdlib.h>
#include <assert.h>

Component_Type POSITION_COMPONENT = "Position";
struct Position
{
	Component info;
	double x, y;
};

Position* Position_create(double x, double y)
{
	Position* self = malloc(sizeof(Position));
	if(!self)
		error(ERROR_ALLOC);
	
	self->info.type = String_create(POSITION_COMPONENT);
	self->x = x;
	self->y = y;
	return self;
}

void Position_destroy(Position** p_component)
{
	assert(p_component && (*p_component));
	String_destroy(&(*p_component)->info.type);
	free((*p_component));
	(*p_component) = NULL;
}

double Position_get_x(const Position* self)
{
	assert(self);
	return self->x;
}

double Position_get_y(const Position* self)
{
	assert(self);
	return self->y;
}


void Position_set_x(Position* self, double x)
{
	assert(self);
	self->x = x;
}

void Position_set_y(Position* self, double y)
{
	assert(self);
	self->y = y;
}
