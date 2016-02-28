#ifndef WINDOW_H
#define WINDOW_H

#include <SDL_2/SDL.h>
typedef struct Window Window;

Window* Window_create(const char* title, 
					  int width, 
					  int height);
void Window_destroy(Window** window);

SDL_Window* Window_get_raw(const Window* self);
SDL_Renderer* Window_get_renderer(const Window* self);
int Window_get_width(const Window* self);
int Window_get_height(const Window* self);
const char* Window_get_title(const Window* self);

void Window_set_width(Window* self, int width);
void Window_set_height(Window* self, int height);
void Window_set_title(Window* self, const char* title);

#endif