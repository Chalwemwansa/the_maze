#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

///Gun class that contains all the guns a player can choose from
class Gun {
	private:
		/* the renderer that will be used to output thing to the screen from the main func */
		SDL_Renderer *renderer = NULL;
		SDL_Texture *gun_texture = NULL;
		SDL_Texture *pistol = NULL;
		SDL_Texture *riffle = NULL;
		SDL_Texture *machine_gun = NULL;
		int gun = 0;
	public:
		/* Gun - constructor to initialise the renderer using the renderer from the main func */
		Gun(SDL_Renderer *renderer)
		{
			this->renderer = renderer;
		}

		///gun_init - function that loads the gun and initialises it for use
		bool gun_init(void)
		{
			/* check if the image png has been initialised properly */
			if (!(IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG))
			{
				fprintf(stderr, "Error initialising image png: %s\n", IMG_GetError());
				return (false);
			}
			/* load gun */
			this->riffle = IMG_LoadTexture(this->renderer, "./textures/riffle.png");
			this->pistol = IMG_LoadTexture(this->renderer, "./textures/pistol.png");
			this->machine_gun = IMG_LoadTexture(this->renderer, "./textures/machine_gun.png");
			/* check if gun was loaded properly */
			if (!(riffle && pistol && machine_gun))
			{
				fprintf(stderr, "Error, failed to load gun: %s\n", IMG_GetError());
				return (false);
			}
			return (true);
		}

		/* change_gun - the function that changes the gun to be renderered onto the screen */
		void change_gun(void)
		{
			this->gun = (this->gun + 1) % 3;
		}

		/// render_gun - function that is used to render the gun to the screen
		void render_gun(void)
		{
			switch (this->gun)
			{
				case 0:
					this->gun_texture = this->pistol;
					break;
				case 1:
					this->gun_texture = this->riffle;
					break;
				case 2:
					this->gun_texture = this->machine_gun;
					break;
				default:
					break;
			}
			SDL_Rect gun_rect = {(SCREEN_WIDTH / 2) - 80, SCREEN_HEIGHT - 252, 160, 250};
			SDL_RenderCopy(this->renderer, gun_texture, NULL, &gun_rect);
		}

		/// renderer_setter - function used to set the renderer for the gun class
		///
		/// @renderer: the renderer used to render things to std out
		void renderer_setter(SDL_Renderer *renderer)
		{
			this->renderer = renderer;
			fprintf(stdout, "renderer set successfully\n");
		}

		~Gun(void)
		{
			/* free up memory after done using the gun */
			SDL_DestroyTexture(this->gun_texture);
			SDL_DestroyTexture(this->pistol);
			SDL_DestroyTexture(this->riffle);
			SDL_DestroyTexture(this->machine_gun);
			IMG_Quit();
		}
};
