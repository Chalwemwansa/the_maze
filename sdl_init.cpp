#include "main.h"

/**
 * sdl_init - initialises and opens up a window for rendering graphics
 *
 * @instance: the sdl instance passed as an argument to the function
 * Return: 0 on success else 1
 */
int sdl_init(SDL_Instance *instance)
{
	/* initialise SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialise SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* create a new window instance from the struct in main.h */
	instance->window = SDL_CreateWindow("the maze by Chalwe", SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	/* check if the window was opened successfully */
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL failed to create window: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* create a renderer instance linked to the instance window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
	/* check if the window was opened successfully */
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/* return 0 on success */
	return (0);
}
