#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Component.h"

extern Component_Type POSITION_COMPONENT;
typedef struct Position_Component Position_Component;

Position_Component* Position_Component_create(double x, double y);
void Position_Component_destroy(Position_Component** p_component);

double Position_Component_get_x(const Position_Component* self);
double Position_Component_get_y(const Position_Component* self);

void Position_Component_set_x(Position_Component* self, double x);
void Position_Component_set_y(Position_Component* self, double y);

#endif