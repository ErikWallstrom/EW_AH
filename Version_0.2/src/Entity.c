#include "Entity.h"
#include "Error.h"
#include "Array.h"
#include <stdlib.h>
#include <assert.h>

struct Entity
{
	String* name;
	Array* components;
};

Entity* Entity_create(const char* name)
{
	Entity* self = malloc(sizeof(Entity));
	if(!self)
		error(ERROR_ALLOC);
	
	self->name = String_create(name);
	self->components = Array_create();
	return self;
}

void Entity_destroy(Entity** entity)
{
	assert(entity && (*entity));
	String_destroy(&(*entity)->name);
	Array_destroy(&(*entity)->components);
	free((*entity));
	(*entity) = NULL;
}

const char* Entity_get_name(const Entity* self)
{
	assert(self);
	return String_get(self->name);
}

bool Entity_has(const Entity* self, Component_Type type)
{
	if(Entity_get(self, type))
	{
		return true;
	}
	return false;
}

void* Entity_get(const Entity* self, Component_Type type)
{
	assert(self);
	foreach(i, self->components)
	{
		Component* component = Array_get(self->components, i);
		if(String_equal(component->type, type))
		{
			return component;
		}
	}
	return NULL;
}

bool Entity_add(Entity* self, void* component)
{
	assert(self && component);
	Component* c = component;
	if(Entity_get(self, String_get(c->type)))
		return false;
	
	Array_insert(self->components, 0, component);
	return true;
}

bool Entity_remove(Entity* self, Component_Type type)
{
	assert(self);
	if(!Entity_get(self, type))
		return false;
	
	foreach(i, self->components)
	{
		Component* component = Array_get(self->components, i);
		if(String_equal(component->type, type))
		{
			Array_remove(self->components, i);
			break;
		}
	}
	return true;
}
