#include "Core.h"
#include "MoveSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include <Windows.h>
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

	if (!InitAudio()) {
		return false;
	}
	    
	loadMedia();


	manager_ = std::make_unique<EntityManager>();
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	auto c = PositionComponent(50, 25);
	auto c2 = PositionComponent(100, 250);
	auto v = VelocityComponent(25.14, -51);
	auto v2 = VelocityComponent(10.99, 0);
	std::vector<Component*> components;
	components.push_back(&c);
	auto id = manager_->create_entity(components);
	std::vector<Component*> components2;
	auto id2 = manager_->create_entity(components2);

	manager_->add_component_to_entity(id, v);
	manager_->add_component_to_entity(id2, v2);
	manager_->add_component_to_entity(id2, c2);


	auto createdComponent = manager_->get_component<PositionComponent>(id);
	std::cout << createdComponent.x << std::endl;
	std::cout << createdComponent.y << std::endl;
	auto createdComponent2 = manager_->get_component<VelocityComponent>(id);
	std::cout << createdComponent2.dx << std::endl;
	std::cout << createdComponent2.dy << std::endl;
	auto list = manager_->get_all_entities<VelocityComponent>();
	for (auto l : list)
	{
		std::cout << l << std::endl;
	}
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
		//Handle key press
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				//Play high sound effect
			case SDLK_1:
				Mix_PlayChannel(0, gHigh, 0);
				break;

				//Play medium sound effect
			case SDLK_2:
				Mix_PlayChannel(0, gMedium, 0);
				break;

				//Play low sound effect
			case SDLK_3:
				Mix_PlayChannel(0, gLow, 0);
				break;

				//Play scratch sound effect
			case SDLK_4:
				PlayAudio(gScratch);
				break;

			case SDLK_9:
				//If there is no music playing
				if (Mix_PlayingMusic() == 0)
				{
					//Play the music
					Mix_PlayMusic(gMusic, 0);
				}
				//If music is being played
				else
				{
					//If the music is paused
					if (Mix_PausedMusic() == 1)
					{
						//Resume the music
						Mix_ResumeMusic();
					}
					//If the music is playing
					else
					{
						//Pause the music
						Mix_PauseMusic();
					}
				}
				break;

			case SDLK_0:
				//Stop the music
				Mix_HaltMusic();
				break;
			default: break;
			}
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
	if (manager_)
	{
		manager_ = nullptr;
	}
	systems_.clear();

	//Free the sound effects
	//Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	//gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	Sleep(5000);
}

bool Core::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load music
	gMusic = Mix_LoadMUS("assets/beat.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	gScratch = "scratch.wav";
	//if (gScratch == NULL)
	//{
	//	printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	//	success = false;
	//}

	gHigh = Mix_LoadWAV("assets/high.wav");
	if (gHigh == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gMedium = Mix_LoadWAV("assets/medium.wav");
	if (gMedium == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gLow = Mix_LoadWAV("assets/low.wav");
	if (gLow == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

