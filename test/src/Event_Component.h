#ifndef EVENT_COMPONENT_H
#define EVENT_COMPONENT_H

	#define COMPONENT_EVENT 1

	typedef struct
	{
		int key_down;
		int key_up;
		int left_click;
		int right_click;
		
	} Event_Component;
	
	Event_Component*	ecomponent_create		(int key_down, int key_up, int left_click, int right_click);

#endif