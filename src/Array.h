#ifndef ARRAY_H
#define ARRAY_H
#pragma once

	typedef struct Array Array;

	Array* array_create(int size);
	void array_destroy(Array* arr);

	int array_getLength		(Array* arr);
	void* array_getValue	(Array* arr, int index);
	int array_setValue		(Array* arr, const int index, void* value);

	int array_popBack		(Array* arr);
	int array_popFront		(Array* arr);
	int array_popAtIndex	(Array* arr, int index);
	
	int array_pushBack		(Array* arr, void* value);
	int array_pushFront		(Array* arr, void* value);
	int array_pushAtIndex	(Array* arr, void* value, int index);

#endif
