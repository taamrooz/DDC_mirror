#include "SDL.h"
#include "SDL_image.h"
#undef main
#ifdef __cplusplus
extern "C"
#endif
#include "AnimationFacade.h"
int main(int argc, char* argv[])
{

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"SDL2Test",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		0
	);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	AnimationFacade a = AnimationFacade(4, "wizard_move_m.png", window, renderer);
	SDL_SetRenderDrawColor(renderer, 0, 100, 0, SDL_ALPHA_OPAQUE);

	
	auto quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		
		SDL_RenderClear(renderer);
		a.updateAnimation();
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
		
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}