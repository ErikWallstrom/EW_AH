#ifndef Position_H
#define Position_H

#include "Component.h"

extern Component_Type POSITION_COMPONENT;
typedef struct Position Position;

Position* Position_create(double x, double y);
void Position_destroy(Position** p_component);

double Position_get_x(const Position* self);
double Position_get_y(const Position* self);

void Position_set_x(Position* self, double x);
void Position_set_y(Position* self, double y);

#endif