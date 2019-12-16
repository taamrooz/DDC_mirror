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
#include "Advertisement.h"
#include "KeyBindingSingleton.h"
#include "EndGameLose.h"
#include "EndGameWin.h"
#include "Pause.h"
#include "SaveHelper.h"
#include "MoveEnemySystem.h"
#include "CheatSystem.h"
#include "DungeonSingleton.h"
#include "TileSetSingleton.h"
#include <ctime>

Core::Core(Engine::SceneManager* manager, bool new_game) : BaseScene(manager), new_game{ new_game } {}
Core::~Core() = default;


bool Core::init()
{
	manager_ = std::make_unique<Engine::EntityManager<Component>>();

	auto endgamewin = new EndGameWin(scene_manager_);
	auto endgamelose = new EndGameLose(scene_manager_);
	auto advertisement = new Advertisement(scene_manager_);
	scene_manager_->add_scene(endgamewin, true, "win");
	scene_manager_->add_scene(endgamelose, true, "lose");
	scene_manager_->add_scene(advertisement, true, "advertisement");

	DungeonSingleton::get_instance()->load_all_dungeons(manager_.get(), new_game);
	
	systems_.push_back(std::make_unique<RoomSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InputSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<MoveCharacterSystem>(manager_.get()));
	
	systems_.push_back(std::make_unique<RenderSystem>(manager_.get()));
	systems_.push_back(std::make_unique<MoveEnemySystem>(manager_.get()));
	systems_.push_back(std::make_unique<CollisionSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<AudioSystem>(manager_.get()));
	systems_.push_back(std::make_unique<ShootSystem>(manager_.get()));
	systems_.push_back(std::make_unique<CheatSystem>(manager_.get(), *this));
	systems_.push_back(std::make_unique<MoveSystem>(manager_.get()));
	systems_.push_back(std::make_unique<InventorySystem>(manager_.get()));
	auto pause = new Pause(scene_manager_,this);
	scene_manager_->add_scene(pause, false, "pause");

	elapsed_secs_ = 0;
	timer_.Start();

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
				timer_.Pause();
				scene_manager_->set_scene("pause");		
				scene_manager_->init();
			}

			if (is_winner_) {
				Engine::stop_music();
				is_winner_ = false;				
				elapsed_secs_ += (timer_.GetTicks() / (double) CLOCKS_PER_SEC);
				scene_manager_->set_scene("win");
				timer_.Stop();
			}

			if (is_loser_) {
				Engine::stop_music();
				is_loser_ = false;
				scene_manager_->set_scene("lose");
				timer_.Stop();			
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
	update();
	Engine::render(timer);
}

void Core::cleanup()
{
	KeyBindingSingleton::get_instance()->reset_properties();
	TileSetSingleton::get_instance()->delete_instance();
	RoomSingleton::get_instance()->delete_instance();
	DungeonSingleton::get_instance()->delete_instance();
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
	if (!is_paused_) {
		timer_.Pause();
	}
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

void Core::save_game(std::string path)
{
	auto sh = SaveHelper{};
	sh.SaveGameToFile(manager_.get(), path);
}

Engine::EntityManager<Component>* Core::get_entity_manager()
{
	return manager_.get();
}

void Core::unpauzeTimer()
{
	if (timer_.IsPaused()) {
	timer_.Unpause();
	}
}
