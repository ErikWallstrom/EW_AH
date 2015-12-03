#ifndef ENTITY_H
#define ENTITY_H

	typedef struct Entity Entity;
	typedef enum
	{
		COMPONENT_GRAPHICS,
		COMPONENT_EVENT
		
	} Component_Type;
	
	Entity* 	entity_create			(const char* name);
	void 		entity_destroy			(Entity** entity);
	void* 		entity_getcomponent		(Entity* entity, Component_Type type);
	int 		entity_addcomponent		(Entity* entity, Component_Type type, void* component);
	int 		entity_removecomponent	(Entity* entity, Component_Type type);
	const char* entity_getname			(Entity* entity);

#endif