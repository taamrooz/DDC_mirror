#include "Core.h"
#undef main
#ifdef __cplusplus
extern "C"
#endif
int main()
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	SDL_Surface* imageSurface = NULL;
	SDL_Surface* windowSurface = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Hello SDL Image world!",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	windowSurface = SDL_GetWindowSurface(window);

	if (window == NULL) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event windowEvent;
	imageSurface = SDL_LoadBMP("Land.bmp");

	if (imageSurface == NULL) {
		std::cout << "SDL could not load image! SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	while (true)
	{
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) {
				break;
			}
		}

		frameStart = SDL_GetTicks();

		SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
		SDL_UpdateWindowSurface(window);

		frameTime = SDL_GetTicks() - frameStart;

		std::cout << "FrameTime: " << frameTime << std::endl;
		std::cout << "FrameDelay: " << frameDelay << std::endl;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}

	SDL_FreeSurface(imageSurface);
	SDL_FreeSurface(windowSurface);

	imageSurface = NULL;
	windowSurface = NULL;

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}