#include "Core.h"

Core Core::Instance;
Core::Core() = default;

bool Core::init(const char* title, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Unable to initialize SDL" << std::endl;
		return false;
	}
	auto flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if ((window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags)) == nullptr)
	{
		std::cout << "Unable to initialize Window" << std::endl;
		return false;
	}
	surf = SDL_GetWindowSurface(window);
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
	{
		std::cout << "Unable to initialize renderer" << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (!(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG))
	{
		std::cout << IMG_GetError() << std::endl;
		std::cout << "Unable to initialize Image" << std::endl;
		return false;
	}
	return true;
}

void Core::input(SDL_Event& event)
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}

}

void Core::update()
{

}

void Core::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

int Core::execute(int argc, char* argv[])
{
	if (!init("Playground", 800, 600, false))
	{
		return 0;
	}
	SDL_Event event;
	while (isRunning)
	{
		input(event);
		update();
		render();
		SDL_Delay(1);
	}

	cleanup();

	return 1;
}

SDL_Renderer* Core::get_renderer() const
{
	return renderer;
}

Core* Core::getInstance()
{
	return &Core::Instance;
}

void Core::cleanup()
{
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	IMG_Quit();
	SDL_Quit();
}

