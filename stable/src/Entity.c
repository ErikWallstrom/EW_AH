#include "Entity.h"
#include "Array.h"
#include "Error.h"

#include <string.h>
#include <stdlib.h>

struct Entity
{
	char* name;
	Array* components;
	Array* component_types;
};

Entity* entity_create(const char* name)
{
	Entity* entity = malloc(sizeof(Entity));
	if(entity == NULL)
	{
		error_popup("Memory allocation failed (entity_create)");
		return NULL;
	}
	
	if(name == NULL)
	{
		entity->name = malloc(sizeof(char));
		if(entity->name == NULL)
		{
			error_popup("Memory allocation failed (entity_create)");
			return NULL;
		}
		entity->name[0] = '\0';
	}
	else
	{
		entity->name = malloc(strlen(name) + 1);
		if(entity->name == NULL)
		{
			error_popup("Memory allocation failed (entity_create)");
			return NULL;
		}
		strcpy(entity->name, name);
	}
	
	entity->components = array_create();
	if(entity->components == NULL)
	{
		return NULL;
	}
	
	entity->component_types = array_create();
	if(entity->component_types == NULL)
	{
		return NULL;
	}
	
	return entity;
}

void entity_destroy(Entity** entity)
{
	if(entity != NULL)
	{
		if((*entity) != NULL)
		{
			if((*entity)->name != NULL)
			{
				free((*entity)->name);
			}
			
			if((*entity)->components != NULL)
			{
				array_destroy(&(*entity)->components);
			}
			
			if((*entity)->component_types != NULL)
			{
				for(int i = 0; i < array_getlength((*entity)->component_types); i++)
				{
					Component_Type* component_type = array_getvalue((*entity)->component_types, i);
					if(component_type != NULL)
					{
						free(component_type);
					}
				}
				array_destroy(&(*entity)->component_types);
			}
			
			free((*entity));
		}
	}
	
	(*entity) = NULL;
}

void* entity_getcomponent(Entity* entity, Component_Type type)
{
	if(entity != NULL)
	{
		for(int i = 0; i < array_getlength(entity->components); i++)
		{
			Component_Type* ctype = array_getvalue(entity->component_types, i);
			if(*ctype == type)
			{
				return array_getvalue(entity->components, i);
			}
		}
	}

	return NULL;
}

int entity_addcomponent(Entity* entity, Component_Type type, void* component)
{
	if(entity != NULL && component != NULL)
	{
		for(int i = 0; i < array_getlength(entity->component_types); i++)
		{
			Component_Type* ctype = array_getvalue(entity->component_types, i);
			if(*ctype == type)
			{
				return 0; //Component already exists
			}
		}
		
		Component_Type* ctype = malloc(sizeof(Component_Type));
		if(ctype == NULL)
		{
			error_popup("Memory allocation failed (entity_addcomponent)");
			return 0;
		} 
		*ctype = type;
		
		array_push(entity->components, 0, component);
		array_push(entity->component_types, 0, ctype);
		
		return 1;
	}
	
	return 0; //Not pushed
}

int entity_removecomponent(Entity* entity, Component_Type type)
{
	if(entity != NULL)
	{
		for(int i = 0; i < array_getlength(entity->component_types); i++)
		{
			Component_Type* ctype = array_getvalue(entity->component_types, i);
			if(*ctype == type)
			{
				array_pop(entity->components, i);
				array_pop(entity->component_types, i);
				
				return 1;
			}
		}
	}
	
	return 0;
}
