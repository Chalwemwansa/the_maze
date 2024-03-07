#ifndef MAIN_H
#define MAIN_H

#define SCREEN_WIDTH 990
#define SCREEN_HEIGHT 560
#define PLANE_HEIGHT 200
#define WALL_SIZE 1
#define PI 3.141592653589793238462643383279502884197
#define FOV (PI / 3)
#define H_WALL 1
#define V_WALL 0
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#include <cmath>
#include "classes/guns.hpp"

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
int events(SDL_Renderer *renderer, double *, double *, double *, bool *, int walls[][28], Gun *);
void event_h(double *, double *, double *, bool *, int walls[][28]);
void draw_walls(SDL_Renderer *, int walls[][28]);
void draw_floor(SDL_Renderer *renderer);
void add_ceiling(SDL_Renderer *renderer);
void raycast(SDL_Renderer *renderer, double posX, double posY, double dirX,
	     int walls[][28]);
void drawline(SDL_Renderer *renderer, int wall_type, int column, double dist);

#endif
