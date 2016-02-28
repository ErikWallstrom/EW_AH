#ifndef DIMENSION_COMPONENT_H
#define DIMENSION_COMPONENT_H

#include "Component.h"
extern Component_Type DIMENSION_COMPONENT;
typedef struct Dimension_Component Dimension_Component;

Dimension_Component* Dimension_Component_create(int width, int height);
void Dimension_Component_destroy(Dimension_Component** d_component);

int Dimension_Component_get_width(const Dimension_Component* self);
int Dimension_Component_get_height(const Dimension_Component* self);

void Dimension_Component_set_width(Dimension_Component* self, int width);
void Dimension_Component_set_height(Dimension_Component* self, int height);

#endif