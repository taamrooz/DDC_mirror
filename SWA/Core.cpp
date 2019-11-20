#include "Core.h"
#include "MoveSystem.h"
#include "InputSystem.h"
#include "RoomSystem.h"
#include "UserInput.h"
#include "AudioSystem.h"
#include <Renderer.h>
#include "RenderSystem.h"
#include "ShootSystem.h"
#include "CollisionSystem.h"
#include "MoveCharacterSystem.h"
#include "CollisionComponent.h"
#include "SceneManager.h"

Core::Core(SceneManager* manager) : BaseScene(manager) {}
Core::~Core() = default;


bool Core::init()
{
	manager_ = std::make_unique<EntityManager>();

	systems_.push_back(std::make_unique<RoomSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InputSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<MoveCharacterSystem>(manager_.get()));
	systems_.push_back(std::make_unique<CollisionSystem>(manager_.get()));
	systems_.push_back(std::make_unique<AudioSystem>(manager_.get()));
	systems_.push_back(std::make_unique<ShootSystem>(manager_.get()));
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	systems_.push_back(std::make_unique<RenderSystem>(manager_.get()));

	return true;
}

void Core::update()
{
	for (auto& system : systems_)
	{
		if(is_running)
		{
			system->update(1);

			if (is_paused) {
				Engine::StopMusic();
				is_paused = false;
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->push_scene();
				scene_manager_->render();
			}
		}else
		{
			break;
		}
		
	}
}

void Core::render()
{
	auto timer = Engine::PreUpdate();
	update();
	Engine::Render(timer);
}

void Core::cleanup()
{
	if (manager_)
	{
		manager_ = nullptr;
	}
	systems_.clear();
}

void Core::StopGameLoop() {
	is_running = false;
}
