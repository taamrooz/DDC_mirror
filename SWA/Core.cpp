#include "Core.h"
#include "MoveSystem.h"

Core Core::instance_;
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
	if ((window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags)) == nullptr)
	{
		std::cout << "Unable to initialize Window" << std::endl;
		return false;
	}
	surf_ = SDL_GetWindowSurface(window_);
	if ((renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
	{
		std::cout << "Unable to initialize renderer" << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
	if (!(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG))
	{
		std::cout << IMG_GetError() << std::endl;
		std::cout << "Unable to initialize Image" << std::endl;
		return false;
	}
	manager_ = std::make_unique<EntityManager>();
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	return true;
}

void Core::input(SDL_Event& event)
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			is_running_ = false;
		}
	}

}

void Core::update()
{
	for (auto& system : systems_)
	{
		system->update(1);
	}
}

void Core::render()
{
	SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);
}

int Core::execute(int argc, char* argv[])
{
	if (!init("Playground", 800, 600, false))
	{
		return 0;
	}
	SDL_Event event;
	while (is_running_)
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
	return renderer_;
}

Core* Core::get_instance()
{
	return &Core::instance_;
}

void Core::cleanup()
{
	if (renderer_)
	{
		SDL_DestroyRenderer(renderer_);
		renderer_ = nullptr;
	}
	if (window_)
	{
		SDL_DestroyWindow(window_);
		window_ = nullptr;
	}
	if(manager_)
	{
		
	}
	IMG_Quit();
	SDL_Quit();
}

