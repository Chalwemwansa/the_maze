#include "main.h"

/**
 * event - handles the events from the events function
 *
 * pos_x: the position of the player in the x-axis
 * pos_y: the position of the player in the y axis
 * dir_x: the direction of the player with respect to the positive x-axis
 * Return: void, does not return anything
 */
void event_h(double *pos_x, double *pos_y, double *dir_x, bool *keys, int walls[][28])
{
	int map_x_pos = int((*pos_x + (0.07 * cos(*dir_x))) / WALL_SIZE);
	int map_x_neg = int((*pos_x - (0.07 * cos(*dir_x))) / WALL_SIZE);
	int map_y_pos = int((*pos_y - (0.07 * sin(*dir_x))) / WALL_SIZE);
	int map_y_neg = int((*pos_y + (0.07 * sin(*dir_x))) / WALL_SIZE);
	int map_x_pos_t = int((*pos_x + (0.009 * cos(*dir_x))) / WALL_SIZE);
	int map_x_neg_t = int((*pos_x - (0.009 * cos(*dir_x))) / WALL_SIZE);
	int map_y_pos_t = int((*pos_y - (0.009 * sin(*dir_x))) / WALL_SIZE);
	int map_y_neg_t = int((*pos_y + (0.009 * sin(*dir_x))) / WALL_SIZE);
	int map_x = int(*pos_x / WALL_SIZE);
	int map_y = int(*pos_y / WALL_SIZE);

	if (keys[UP] == true)
	{
		if (walls[map_y][map_x_pos] != 1)
			*pos_x += (0.07 * cos(*dir_x));
		else
			*pos_x -= (0.03 * cos(*dir_x));
		if (walls[map_y_pos][map_x] != 1)
			*pos_y -= (0.07 * sin(*dir_x));
		else
			*pos_y += (0.03 * sin(*dir_x));
	}
	if ((keys[UP] == true) && (keys[LEFT] == true))
	{
		*dir_x += (PI / 180);
		if (walls[map_y][map_x_pos_t] != 1)
			*pos_x += (0.009 * cos(*dir_x));
		else
			*pos_x -= (0.02 * cos(*dir_x));
		if (walls[map_y_pos_t][map_x] != 1)
			*pos_y -= (0.009 * sin(*dir_x));
		else
			*pos_y += (0.02 * sin(*dir_x));
	}
	if ((keys[UP] == true) && (keys[RIGHT] == true))
	{
		*dir_x -= (PI / 180);
		if (walls[map_y][map_x_pos_t] != 1)
			*pos_x += (0.009 * cos(*dir_x));
		else
			*pos_x -= (0.02 * cos(*dir_x));
		if (walls[map_y_pos_t][map_x] != 1)
			*pos_y -= (0.009 * sin(*dir_x));
		else
			*pos_y += (0.02 * sin(*dir_x));
	}
	if (keys[DOWN] == true)
	{
		if (walls[map_y][map_x_neg] != 1)
			*pos_x -= (0.07 * cos(*dir_x));
		if (walls[map_y_neg][map_x] != 1)
			*pos_y += (0.07 * sin(*dir_x));
	}
	if (keys[LEFT] == true)
	{
		*dir_x += (PI / 90);
		if (*dir_x > (2 * PI))
			*dir_x -= (2 * PI);
	}
	if (keys[RIGHT] == true)
	{
		*dir_x -= (PI / 90);
		if (*dir_x < 0)
			*dir_x += (2 * PI);
	}
}
/**
 * events - handles keyboard events like key presses
 *
 * dir_x: the players direction with respect to the x-axis
 * return: 0 on success else 1
 */
int events(SDL_Renderer *renderer, double *pos_x, double *pos_y, double *dir_x, bool *keys, int walls[][28], Gun *gun)
{
	SDL_Event event;
	SDL_KeyboardEvent key;
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (1);
		if (event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:
					*(keys + LEFT) = true;
					break;
				case SDLK_RIGHT:
					*(keys + RIGHT) = true;
					break;
				case SDLK_UP:
					*(keys + UP) = true;
					break;
				case SDLK_DOWN:
					*(keys + DOWN) = true;
					break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_LEFT:
					*(keys + LEFT) = false;
					break;
				case SDLK_RIGHT:
					*(keys + RIGHT) = false;
					break;
				case SDLK_UP:
					*(keys + UP) = false;
					break;
				case SDLK_DOWN:
					*(keys + DOWN) = false;
					break;
				case SDLK_c:
					gun->change_gun();
					break;
			}
		}
		raycast(renderer, *pos_x, *pos_y, *dir_x, walls);
		gun->render_gun();
	}
	event_h(pos_x, pos_y, dir_x, keys, walls);
	raycast(renderer, *pos_x, *pos_y, *dir_x, walls);
	gun->render_gun();
	return (0);
}
