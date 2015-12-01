#ifndef ARRAY_H
#define ARRAY_H
#pragma once

	typedef struct Array Array;

	Array* 	array_create		(void);
	void 	array_destroy		(Array* array);
	int 	array_pop			(Array* array, int index);
	int 	array_push			(Array* array, int index, void* value);
	int 	array_getlength		(Array* array);
	void* 	array_getvalue		(Array* array, int index);
	int 	array_setvalue		(Array* array, int index, void* value);

#endif
