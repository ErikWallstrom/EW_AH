#include "Entity.h"

#include "Array.h"
#include "Script.h"

#include <string.h>
#include <stdlib.h>

struct Entity
{
	char* name;
	Array* components;
	Array* component_types;
};

Entity* entity_create(lua_State* script, SDL_Renderer* renderer, const char* name)
{
	Entity* entity = malloc(sizeof(Entity));
	if(entity == NULL)
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			"Memory allocation failed (load_entity)", 
			NULL
		);
		return NULL;
	}

	entity->component_types = array_create();
	entity->components = array_create();
	
	entity->name = malloc(strlen(name) + 1);
	if(entity->name == NULL)
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			"Memory allocation failed (load_entity)", 
			NULL
		);
		return NULL;
	}
	strcpy(entity->name, name);
	
	char* buffer = malloc(strlen(name) + sizeof(".graphics_component"));
	if(buffer == NULL)
	{
		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR, 
			"Error", 
			"Memory allocation error (entity_create)", 
			NULL
		);
			
		return NULL;
	}
		
	strcpy(buffer, name);
	strcpy(buffer + strlen(name), ".graphics_component");
	if(!script_getnil(script, buffer))
	{
		Graphics_Component* gcomponent = malloc(sizeof(Graphics_Component));
		buffer = realloc(buffer, strlen(buffer) + sizeof(".height"));
		if(buffer == NULL)
		{
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR, 
				"Error", 
				"Memory allocation error (entity_create)", 
				NULL
			);
			
			return NULL;
		}
		
		strcpy(buffer + strlen(name) + sizeof(".graphics_component") - 1, ".file");
		gcomponent->texture = IMG_LoadTexture(renderer, script_getstring(script, buffer));
		if(gcomponent->texture == NULL)
		{
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR, 
				"Error", 
				IMG_GetError(), 
				NULL
			);
			
			return NULL;
		}
		
		strcpy(buffer + strlen(name) + sizeof(".graphics_component") - 1, ".x");
		gcomponent->x = script_getnumber(script, buffer);
		strcpy(buffer + strlen(name) + sizeof(".graphics_component") - 1, ".y");
		gcomponent->y = script_getnumber(script, buffer);
		strcpy(buffer + strlen(name) + sizeof(".graphics_component") - 1, ".width");
		gcomponent->width = script_getinteger(script, buffer);
		strcpy(buffer + strlen(name) + sizeof(".graphics_component") - 1, ".height");
		gcomponent->height = script_getinteger(script, buffer);
		
		Component_Type* type = malloc(sizeof(Component_Type));
		if(type == NULL)
		{
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_ERROR, 
				"Error", 
				"Memory allocation error (entity_create)", 
				NULL
			);
			
			return NULL;
		}
		
		*type = GRAPHICS;
		
		array_push(entity->component_types, 0, type);
		array_push(entity->components, 0, gcomponent);
	}
	
	return entity;
}

void entity_destroy(Entity* entity)
{
	if(entity != NULL)
	{
		if(entity->name != NULL)
		{
			free(entity->name);
		}
		
		if(entity->components != NULL)
		{
			for(int i = 0; i < array_getlength(entity->components); i++)
			{
				Component_Type* component_type = array_getvalue(entity->component_types, i);
				if(*component_type == GRAPHICS)
				{
					Graphics_Component* gcomponent = array_getvalue(entity->components, i);
					if(gcomponent != NULL)
					{
						SDL_DestroyTexture(gcomponent->texture);
					}
				}
			}
			array_destroy(entity->components);
		}
		
		if(entity->component_types != NULL)
		{
			for(int i = 0; i < array_getlength(entity->component_types); i++)
			{
				Component_Type* component_type = array_getvalue(entity->component_types, i);
				if(component_type != NULL)
				{
					free(component_type);
				}
			}
			array_destroy(entity->component_types);
		}
		
		free(entity);
	}
}

void* entity_getcomponent(Entity* entity, Component_Type component)
{
	for(int i = 0; array_getlength(entity->components); i++)
	{
		Component_Type* type = array_getvalue(entity->component_types, i);
		if(*type == component)
		{
			return array_getvalue(entity->components, i);
		}
	}
	
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_WARNING, 
		"Warning", 
		"Component not found (entity_create)", 
		NULL
	);
	return NULL;
}
