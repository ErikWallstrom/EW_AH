#include "Event_Component.h"
#include "Error.h"
#include <stdlib.h>

Event_Component* ecomponent_create(int key_down, int key_up, int left_click, int right_click)
{
	Event_Component* ecomponent = malloc(sizeof(Event_Component));
	if(ecomponent == NULL)
	{
		error_popup("Memory allocation error");
		return NULL;
	}
	
	ecomponent->key_down = key_down;
	ecomponent->key_up = key_up;
	ecomponent->left_click = left_click;
	ecomponent->right_click = right_click;
	
	return ecomponent;
}