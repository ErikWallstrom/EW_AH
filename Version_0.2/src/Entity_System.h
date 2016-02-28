#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include "Window.h"
#include "Entity.h"
#include <stdbool.h>

typedef struct Entity_System Entity_System;

Entity_System* Entity_System_create(const Window* window);
void Entity_System_destroy(Entity_System** e_system);

bool Entity_System_add(Entity_System* self, Entity* entity);
void Entity_System_load(Entity_System* self, const char* file);
void Entity_System_start(Entity_System* self);

#endif