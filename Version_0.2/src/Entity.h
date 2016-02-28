#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include <stdbool.h>

typedef struct Entity Entity;

Entity* Entity_create(const char* name);
void Entity_destroy(Entity** entity);

bool Entity_has(const Entity* self, Component_Type type);
const char* Entity_get_name(const Entity* self);
void* Entity_get(const Entity* self, Component_Type type);

bool Entity_add(Entity* self, void* component);
bool Entity_remove(Entity* self, Component_Type type);

#endif