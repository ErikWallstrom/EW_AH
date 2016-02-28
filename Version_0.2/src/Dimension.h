#ifndef Dimension_H
#define Dimension_H

#include "Component.h"
extern Component_Type DIMENSION_COMPONENT;
typedef struct Dimension Dimension;

Dimension* Dimension_create(int width, int height);
void Dimension_destroy(Dimension** d_component);

int Dimension_get_width(const Dimension* self);
int Dimension_get_height(const Dimension* self);

void Dimension_set_width(Dimension* self, int width);
void Dimension_set_height(Dimension* self, int height);

#endif