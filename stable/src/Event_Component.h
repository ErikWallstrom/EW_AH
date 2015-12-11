#ifndef EVENT_COMPONENT_H
#define EVENT_COMPONENT_H

	#define COMPONENT_EVENT 1
	#include "Array.h"

	typedef struct
	{
		Array* keys_down; //Key up/down events
		
	} Event_Component;
	
	Event_Component* ecomponent_create(void);

#endif
