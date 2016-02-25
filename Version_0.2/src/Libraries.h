#ifndef LIBRARIES_H
#define LIBRARIES_H

#include <SDL_2/SDL.h>
#include <SDL_2/SDL_image.h>
#include <SDL_2/SDL_net.h>
#include <SDL_2/SDL_ttf.h>
#include <SDL_2/SDL_mixer.h>

void Libraries_initialize(void);
void Libraries_terminate(void);

#endif