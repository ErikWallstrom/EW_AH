#include "String.h"
#include "Error.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct String
{
	char* raw;
	size_t size;
};

String* String_create(const char* string)
{
	assert(string);
    String* self = malloc(sizeof(String));
    if(!self)
		error(ERROR_ALLOC);
	
	self->raw = NULL;
    String_set(self, string);
    return self;
}

void String_destroy(String** string)
{
	assert(string && (*string));
    free((*string)->raw);
    free((*string));

    *string = NULL;
}

size_t String_length(const String* self)
{
	assert(self);
    return self->size - 1;
}

const char* String_get(const String* self)
{
	assert(self);
	return self->raw;
}

bool String_equal(const String* self, const char* string)
{
	assert(self && string);
	if(strcmp(self->raw, string))
	{
		return false;
	}
	return true;
}

void String_set(String* self, const char* string)
{
	assert(self && string);
	size_t string_size = strlen(string) + 1;
	if(self->size != string_size)
	{
		void* string_raw = malloc(string_size);
		if(!string_raw)
			error(ERROR_ALLOC);

		free(self->raw);
		self->raw = string_raw;
		self->size = string_size;
	}
	strcpy(self->raw, string);
}

void String_append(String* self, const char* string)
{
	assert(self && string);
	size_t string_size = self->size + strlen(string);
	void* string_raw = realloc(self->raw, string_size);
	if(!string_raw)
		error(ERROR_ALLOC);

	strcat(string_raw, string);

	self->raw = string_raw;
	self->size = string_size;
}

void String_prepend(String* self, const char* string)
{
	assert(self && string);
	size_t string_size = self->size + strlen(string);
	void* string_raw = malloc(string_size);
	if(!string_raw)
		error(ERROR_ALLOC);

	strcpy(string_raw, string);
	strcat(string_raw, self->raw);

	free(self->raw);
	self->raw = string_raw;
	self->size = string_size;
}
