#include "Array.h"
#include "Error.h"
#include <stdlib.h>

struct Array
{
	void** value;
	int max_size;
	int used_size;
};

Array* array_create(void)
{
	Array* array = malloc(sizeof(Array));
	if (array == NULL) //If error
	{
		error_popup("Memory allocation failed (array_create)");
		return NULL;
	}

	array->value = malloc(sizeof(void*));
	if (array->value == NULL) //If error
	{
		error_popup("Memory allocation failed (array_create)");
		return NULL;
	}

	array->max_size = 1;
	array->used_size = 0;

	return array;
}

void array_destroy(Array** array)
{
	if (array != NULL)
	{
		if((*array) != NULL)
		{
			if((*array)->value != NULL)
			{
				free((*array)->value);
			}
			
			free((*array));
		}
	}
	
	(*array) = NULL;
}

int array_pop(Array* array, int index)
{
	if (index < array->used_size && index >= 0 && array->used_size > 0)
	{

		for (int i = index; i < array->used_size; i++)
		{
			array->value[i] = array->value[i + 1];
		}

		void* newMem = realloc(array->value, sizeof(void*) * ((array->used_size > 1) ? (array->used_size - 1) : (1)));
		if (newMem == NULL) //If error
		{
			error_popup("Memory allocation failed (array_pop)");
			return 0;
		}

		array->value = newMem;
		array->max_size--;
		array->used_size--;

		return 1;
	}

	return 0; //If error
}

int array_push(Array* array, int index, void* value)
{
	if (index < array->used_size + 1 && index >= 0)
	{
		if (array->used_size >= array->max_size)
		{
			void* newMem = realloc(array->value, sizeof(void*) * (array->max_size + 1));
			if (newMem == NULL) //If error
			{
				error_popup("Memory allocation failed (array_push)");
				return 0;
			}

			array->value = newMem;
			array->max_size++;
		}

		for (int i = array->used_size; i > index; i--)
		{
			array->value[i] = array->value[i - 1];
		}

		array->value[index] = value;
		array->used_size++;

		return 1;
	}

	return 0; //If error
}

int array_getlength(Array* array)
{
	return array->used_size;
}

void* array_getvalue(Array* array, int index)
{
	if (index < array->used_size && index >= 0)
	{
		return array->value[index];
	}

	return NULL; //If error
}

int array_setvalue(Array* array, const int index, void* value)
{
	if (index < array->used_size && index >= 0)
	{
		array->value[index] = value;
		return 1;
	}

	return 0; //If error
}
