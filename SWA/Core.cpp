#include "Core.h"
#include "MoveSystem.h"
#include "InputSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include <Windows.h>
#include "UserInput.h"
#include "AudioSystem.h"

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

	if (!Engine::InitAudio()) {
		return false;
	}
	loadMedia();


	manager_ = std::make_unique<EntityManager>();
	inputcomponent_ = std::make_unique<InputComponent>();
	systems_.push_back(std::make_unique<InputSystem>(manager_.get(), inputcomponent_.get(), *this));
	systems_.push_back(std::make_unique<AudioSystem>(manager_.get(), inputcomponent_.get()));
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	std::vector<std::shared_ptr<Component>> components;
	components.push_back(std::make_shared<PositionComponent>(50, 25));
	const auto id = manager_->create_entity(components);
	const auto id2 = manager_->create_entity();

	manager_->add_component_to_entity(id, std::make_shared<VelocityComponent>(14, -51));
	manager_->add_component_to_entity(id2, std::make_shared<VelocityComponent>(10.99, 0));
	manager_->add_component_to_entity(id2, std::make_shared<PositionComponent>(100, 250));


	const auto createdComponent = manager_->get_component<PositionComponent>(id);
	std::cout << createdComponent.x << std::endl;
	std::cout << createdComponent.y << std::endl;
	const auto createdComponent2 = manager_->get_component<VelocityComponent>(id);
	std::cout << createdComponent2.dx << std::endl;
	std::cout << createdComponent2.dy << std::endl;
	auto list = manager_->get_all_entities<VelocityComponent>();
	for (auto l : list)
	{
		std::cout << l << std::endl;
	}
	return true;
}

void Core::input()
{
	auto user_inputs = Engine::GetInputs();
	if (!user_inputs.second) {
		is_running_ = false;
		return;
	}
	for (const auto& keycode : user_inputs.first)
	{
		switch (keycode)
		{
			//Play high sound effect
		case SDLK_1:
			Engine::PlayAudio(gHigh);
			break;

			//Play medium sound effect
		case SDLK_2:
			Engine::PlayAudio(gMedium);
			break;

			//Play low sound effect
		case SDLK_3:
			Engine::PlayAudio(gLow);
			break;

			//Play scratch sound effect
		case SDLK_4:
			Engine::PlayAudio(gScratch);
			break;

		case SDLK_9:
			//Play the music
			Engine::PlayMusic(gMusic);
			break;

		case SDLK_0:
			//Stop the music
			Engine::StopMusic();
			break;
		default: break;
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
		//input();

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

	Engine::CloseAudio(); //Free up audio chunks and execute MIX_Quit()

	IMG_Quit();
	SDL_Quit();
}

void Core::loadMedia()
{
	//Load music
	gMusic = "beat.wav";
	gScratch = "scratch.wav";
	gHigh = "high.wav";
	gMedium = "medium.wav";
	gLow = "low.wav";
}

void Core::StopGameLoop() {
	is_running_ = false;
}
