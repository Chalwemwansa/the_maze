#include "main.h"

/**
 * main - calls the sdl_init program
 * and all the different classes needed for the game
 *
 * return: 0 on success
 */
int main(void)
{
	SDL_Instance instance;

	if (sdl_init(&instance) != 0)
		return (1);

	while ("infinite game loop")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		if (events() == 1)
			break;
		SDL_RenderPresent(instance.renderer);
	}

	SDL_DestroyWindow(instance.window);
	SDL_DestroyRenderer(instance.renderer);

	return (0);
}
