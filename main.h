#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdio.h>

/**
 * SDL_Instance - the structure that holds the sdl window and renderer
 *
 * window: the window that will open up on the screen
 * renderer: the sdl renerer used to render things to the window
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/* helper functions for the project */
int sdl_init(SDL_Instance *);
int events(void);

#endif
