#ifndef ENTITY_H
#define ENTITY_H

	typedef struct Entity Entity;
	
	Entity* 	entity_create			(const char* name);
	void 		entity_destroy			(Entity** entity);
	void* 		entity_getcomponent		(Entity* entity, int type);
	int 		entity_addcomponent		(Entity* entity, int type, void* component);
	int 		entity_removecomponent	(Entity* entity, int type);
	const char* entity_getname			(Entity* entity);

#endif