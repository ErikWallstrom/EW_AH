#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdbool.h>

typedef struct String String;

String* String_create(const char* string);
void String_destroy(String** string);

size_t String_length(const String* self);
const char* String_get(const String* self);
bool String_equal(const String* self, const char* string);

void String_set(String* self, const char* string);
void String_append(String* self, const char* string);
void String_prepend(String* self, const char* string);

#endif
