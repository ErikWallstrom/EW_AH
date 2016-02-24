#include "Event_Component.h"
#include "Error.h"
#include "Array.h"
#include <stdlib.h>

Event_Component* ecomponent_create(void)
{
	Event_Component* ecomponent = malloc(sizeof(Event_Component));
	if(ecomponent == NULL)
	{
		error_popup("Memory allocation error");
		return NULL;
	}
	
	ecomponent->keys_down = array_create();
	return ecomponent;
}