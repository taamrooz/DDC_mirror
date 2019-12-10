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
#include "InventorySystem.h"
#include "Audio.h"
#include "KeyBindingSingleton.h"
#include "MoveEnemySystem.h"
#include "CheatSystem.h"
#include <chrono>

Core::Core(Engine::SceneManager* manager) : BaseScene(manager) {}
Core::~Core() = default;


bool Core::init()
{
	manager_ = std::make_unique<Engine::EntityManager<Component>>();

	systems_.push_back(std::make_unique<RoomSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InputSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<MoveCharacterSystem>(manager_.get()));
	systems_.push_back(std::make_unique<MoveEnemySystem>(manager_.get()));
	systems_.push_back(std::make_unique<RenderSystem>(manager_.get()));
	systems_.push_back(std::make_unique<CollisionSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<AudioSystem>(manager_.get()));
	systems_.push_back(std::make_unique<ShootSystem>(manager_.get()));
	systems_.push_back(std::make_unique<CheatSystem>(manager_.get()));
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InventorySystem>(manager_.get()));

	timer_start_ = std::clock();

	return true;
}

void Core::update()
{
	for (auto& system : systems_)
	{
		if(is_running_)
		{
			system->update(1);

			if (is_paused_) {
				Engine::pause_music();
				is_paused_ = false;
				scene_manager_->set_scene("pause");
			}

			if (is_winner_) {
				Engine::stop_music();
				is_winner_ = false;
				scene_manager_->set_scene("win");
				auto timer_end = std::chrono::high_resolution_clock::now();
				timer_end_ = std::clock();
				double elapsed_secs = double(timer_start_ - timer_end_) / CLOCKS_PER_SEC;
			}

			if (is_loser_) {
				Engine::stop_music();
				is_loser_ = false;
				scene_manager_->set_scene("lose");
			}
		}else
		{
			break;
		}
		
	}
}

void Core::render()
{
	auto timer = Engine::pre_update();
	//Engine::Clear();
	update();
	Engine::render(timer);
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
	is_running_ = false;
}

bool Core::get_is_paused() const
{
	return is_paused_;
}

void Core::toggle_pause()
{
	is_paused_ = !is_paused_;
}

void Core::toggle_game_won()
{
	is_winner_ = !is_winner_;
	KeyBindingSingleton::get_instance()->reset_properties();
}

void Core::toggle_game_lost()
{
	is_loser_ = !is_loser_;
	KeyBindingSingleton::get_instance()->reset_properties();
}
