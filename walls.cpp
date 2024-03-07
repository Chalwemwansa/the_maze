#include "main.h"

/**
 * draw_walls - the function draws walls in the maze game
 *
 * renderer: the pointer to the renderer that is being used
 * walls: the 2 dimenssional map for the world
 * return: void, the function does not return anything
 */
void draw_walls(SDL_Renderer *renderer, int walls[][28])
{
	SDL_Rect wall;

	/* set the color of the walls using RGB system */
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	/* draw the walls using two for loops */
	for (int i = 0; i < (SCREEN_HEIGHT / WALL_SIZE); i++)
	{
		for (int j = 0; j < (SCREEN_WIDTH / WALL_SIZE); j++)
		{
			if (walls[i][j] == 1)
			{
				wall = {j * WALL_SIZE, i * WALL_SIZE, WALL_SIZE, WALL_SIZE};
				SDL_RenderFillRect(renderer, &wall);
			}
		}
	}
}

/**
 * raycast - function that is responsible for printing 3d world from a map
 *
 * renderer: the renderer to draw stuff to
 * posx: the x-coordinate possition for player
 * posY: the y coordinate of the player
 * dirX: the angle of the player with respect to the x-axis
 * walls: the array containing the walls of the maze
 */
void raycast(SDL_Renderer *renderer, double pos_x, double pos_y, double dir_x,
	     int walls[][28])
{
	/* the increment that will be made to the angles during casting */
	double angle_step = FOV / (double)SCREEN_WIDTH;
	/* the angle casting of rays begin from with respect to the positive x-axis*/
	double start_angle;
	/* the angle of the ray with respect to the positive x-axis */
	double alpha, beta, wall_distance;
	/* the distance from player to a wall/box at start of algorithm */
	double dist_x, dist_y;
	/* the distance to be adding to the dist in x and y if wall is not hit yet */
	double delta_x, delta_y;
	/* the step to take to move from box to box */
	int step_x, step_y;
	/* the variables that store the position on the map */
	int map_x, map_y, wall_type;


	draw_floor(renderer);
	if ((dir_x + (FOV / 2)) >= (2.0 * PI))
		start_angle = (dir_x + (FOV / 2)) - (2.0 * PI);
	else
		start_angle = dir_x + (FOV / 2);
	
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		map_x = int(pos_x / WALL_SIZE);
		map_y = int(pos_y / WALL_SIZE);
		dist_x = 0, dist_y = 0;
		beta = start_angle - angle_step * x;
		beta = (beta < 0) ? (2 * PI) +  beta : beta;
		/* find the smallest angle with respect to the x-axis */
		alpha = (cos(beta) == 0 || sin(beta) == 0) ? beta : fabs(atan(sin(beta) / cos(beta)));
		delta_x = (cos(alpha) == 0) ? 0: (WALL_SIZE / cos(alpha));
		delta_y = (sin(alpha) == 0) ? 0: (WALL_SIZE / sin(alpha));

		if ((beta < (PI / 2)) || (beta > (3 * PI) / 2))
		{
			step_x = 1;
			dist_x = (((map_x + 1) * WALL_SIZE) - pos_x) / fabs(cos(alpha));
		}
		if ((beta > (PI / 2)) && (beta < ((3 * PI) / 2)))
		{
			step_x = -1;
			dist_x = (pos_x - (map_x * WALL_SIZE)) / fabs(cos(alpha));
		}
		if ((beta > PI) && (beta < (2 * PI)))
		{
			step_y = 1;
			dist_y = (((map_y + 1) * WALL_SIZE) - pos_y) / fabs(sin(alpha));
		}
		if ((beta < PI) && (beta > 0))
		{
			step_y = -1;
			dist_y = (pos_y - (map_y * WALL_SIZE)) / fabs(sin(alpha));
		}

		while ("checking if wall is hit")
		{
			if (((dist_x < dist_y) && (dist_x != 0)) || (dist_y == 0))
			{
				map_x += step_x;
				wall_type = V_WALL;
			}
			else
			{
				map_y += step_y;
				wall_type = H_WALL;
			}

			if (walls[map_y][map_x] > 0)
			{
				if (wall_type == V_WALL)
					wall_distance = dist_x * cos(fabs((PI / 6) - (angle_step * x)));
				else
					wall_distance = dist_y * cos(fabs((PI / 6) - (angle_step * x)));
				break;
			}
			if (wall_type == V_WALL)
				dist_x += delta_x;
			else
				dist_y += delta_y;
		}
		drawline(renderer, wall_type, x, wall_distance);
	}
}

/**
 * drawline - function draws a vertical line
 *
 * renderer: the renderer to right to
 * wall_type: the type of wall
 * column: the column to draw a line in
 * dist: the distance to the wall
 */
void drawline(SDL_Renderer *renderer, int wall_type, int column, double dist)
{
	double wall_height;

	if (wall_type == V_WALL)
		SDL_SetRenderDrawColor(renderer, 0, 0, 60, 255);
		//SDL_SetRenderDrawColor(renderer, 0, 40, 0, 255);
	else
		SDL_SetRenderDrawColor(renderer, 0, 0, 70, 255);
		//SDL_SetRenderDrawColor(renderer, 0, 50, 0, 255);
	/* Calculate wall height based on distance */
	wall_height = double(PLANE_HEIGHT) / dist;

	/* Ensure the wall height is within the screen bounds */
	if (wall_height > SCREEN_HEIGHT)
		wall_height = SCREEN_HEIGHT;

	/* Calculate top and bottom positions of the wall */
	double top = (double)SCREEN_HEIGHT / 2 - wall_height / 2;
	double bottom = (double)SCREEN_HEIGHT / 2 + wall_height / 2;
	/* Draw the line representing the wall */
	SDL_RenderDrawLine(renderer, column, (int)top, column, (int)bottom);
}
