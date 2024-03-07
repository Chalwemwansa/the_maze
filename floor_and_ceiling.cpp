#include "main.h"
/**
 * draw_floor - function draws the floor on the screen by casting rays on the screen
 * 	horizontally
 * 
 * renderer: the renderer that will bbe used to draw the lines on the screen
 * return: void, does not return anything
 */

void draw_floor(SDL_Renderer *renderer)
{
	for (int x = 0; x < (SCREEN_HEIGHT / 2); x++)
	{
		int cod_y =  (SCREEN_HEIGHT / 2) + x;

		SDL_SetRenderDrawColor(renderer, 0, 0, 30, 200);
		SDL_RenderDrawLine(renderer, 0, cod_y, SCREEN_WIDTH, cod_y);
	}
}

void add_ceiling(SDL_Renderer *renderer)
{
	SDL_Texture *night = NULL;
	if (!(IMG_Init(IMG_INIT_JPG) && IMG_INIT_JPG))
	{
		fprintf(stderr, "Error initialising image png: %s\n", IMG_GetError());
		return;
	}

	night = IMG_LoadTexture(renderer, "./textures/night_sky.jpg");
	if (!night)
	{
		fprintf(stderr, "error loading sky: %s\n", IMG_GetError());
		return;
	}

	SDL_Rect night_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
	SDL_RenderCopy(renderer, night, NULL, &night_rect);
	SDL_DestroyTexture(night);
}
