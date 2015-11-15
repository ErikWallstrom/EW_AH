#include "Array.h"
#include <stdlib.h>

struct Array
{
	void** value;
	int max_size;
	int used_size;
	int prefered_size;
};

Array* array_create(int size)
{
	Array* arr = malloc(sizeof(Array));
	if (arr == NULL) //If error
	{
		return NULL;
	}

	arr->value = calloc(size, sizeof(void*));
	if (arr->value == NULL) //If error
	{
		return NULL;
	}

	arr->max_size = size;
	arr->used_size = 0;
	arr->prefered_size = size;

	return arr;
}

void array_destroy(Array* arr)
{
	if (arr != NULL)
	{
		free(arr->value);
		arr->max_size = 0;
		arr->used_size = 0;
		arr->prefered_size = 0;

		free(arr);
	}
}

int array_getLength(Array* arr)
{
	return arr->used_size;
}

void* array_getValue(Array* arr, int index)
{
	if (index < arr->used_size && index >= 0)
	{
		return arr->value[index];
	}

	return NULL; //If error
}

int array_setValue(Array* arr, const int index, void* value)
{
	if (index < arr->used_size && index >= 0)
	{
		arr->value[index] = value;
		return 1;
	}

	return 0; //If error
}

int array_popBack(Array* arr)
{
	if (arr->used_size > 0)
	{
		if (arr->max_size - 1 > arr->prefered_size)
		{
			void* newMem = realloc(arr->value, sizeof(void*) * (arr->max_size - 1));
			if (newMem == NULL) //If error
			{
				return 0;
			}

			arr->value = newMem;
			arr->max_size--;
			arr->used_size--;
		}
		else
		{
			arr->value[arr->used_size - 1] = NULL;
			arr->used_size--;
		}
	}

	return 1;
}

int array_popFront(Array* arr)
{
	if (arr->used_size > 0)
	{
		for (int i = 0; i < arr->used_size; i++)
		{
			arr->value[i] = arr->value[i + 1];
		}

		if (arr->max_size - 1 > arr->prefered_size)
		{
			void* newMem = realloc(arr->value, sizeof(void*) * (arr->max_size - 1));
			if (newMem == NULL) //If error
			{
				return 0;
			}

			arr->value = newMem;
			arr->max_size--;
			arr->used_size--;
		}
		else
		{
			arr->value[arr->used_size - 1] = NULL;
			arr->used_size--;
		}
	}

	return 1;
}

int array_popAtIndex(Array* arr, int index)
{
	if (index < arr->used_size && index >= 0)
	{
		if (arr->used_size > 0)
		{
			for (int i = index; i < arr->used_size; i++)
			{
				arr->value[i] = arr->value[i + 1];
			}

			if (arr->max_size - 1 > arr->prefered_size)
			{
				void* newMem = realloc(arr->value, sizeof(void*) * (arr->max_size - 1));
				if (newMem == NULL) //If error
				{
					return 0;
				}

				arr->value = newMem;
				arr->max_size--;
				arr->used_size--;
			}
			else
			{
				arr->value[arr->used_size - 1] = NULL;
				arr->used_size--;
			}
		}

		return 1;
	}

	return 0; //If error
}

int array_pushBack(Array* arr, void* value)
{
	if (arr->used_size >= arr->max_size)
	{
		void* newMem = realloc(arr->value, sizeof(void*) * (arr->max_size + 1));
		if (newMem == NULL) //If error
		{
			return 0;
		}

		arr->value = newMem;
		arr->max_size++;
	}

	arr->value[arr->used_size] = value;
	arr->used_size++;

	return 1;
}

int array_pushFront(Array* arr, void* value)
{
	if (arr->used_size >= arr->max_size)
	{
		void* newMem = realloc(arr->value, sizeof(void*) * (arr->max_size + 1));
		if (newMem == NULL) //If error
		{
			return 0;
		}

		arr->value = newMem;
		arr->max_size++;
	}

	for (int i = arr->used_size; i > 0; i--)
	{
		arr->value[i] = arr->value[i - 1];
	}

	arr->value[0] = value;
	arr->used_size++;

	return 1;
}

int array_pushAtIndex(Array* arr, void* value, int index)
{
	if (index < arr->used_size && index >= 0)
	{
		if (arr->used_size >= arr->max_size)
		{
			void* newMem = realloc(arr->value, sizeof(void*) * (arr->max_size + 1));
			if (newMem == NULL) //If error
			{
				return 0;
			}

			arr->value = newMem;
			arr->max_size++;
		}

		for (int i = arr->used_size; i > index; i--)
		{
			arr->value[i] = arr->value[i - 1];
		}

		arr->value[index] = value;
		arr->used_size++;

		return 1;
	}

	return 0; //If error
}
