#include "RoomSystem.h"
#include "TileComponent.h"
#include "RoomSingleton.h"
#include "PositionComponent.h"
#include "ComponentFactory.h"
#include "CollisionHandlers.h"
#include "LevelSingleton.h"
#include <Audio.h>
#include "LevelBossComponent.h"
#include "CharacterComponent.h"

RoomSystem::RoomSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager)
{}

void RoomSystem::update(double dt)
{
	if (LevelSingleton::get_instance()->reload_level || RoomSingleton::get_instance()->reload_room) {
		auto room_entities = manager_->get_all_entities_from_current_room<PositionComponent>();
		if(room_entities.empty())
		{
			LevelSingleton::get_instance()->load_room(manager_);
		}
		

		RoomSingleton::get_instance()->reload_room = false;
		LevelSingleton::get_instance()->reload_level = false;

		const auto boss_entities = manager_->get_all_entities_from_current_room<LevelBossComponent>();
		if (!boss_entities.empty()) {
			Engine::stop_music();
			Engine::play_music("danger.wav");
		}
	}
	auto entity = manager_->get_all_entities_from_current_room<CharacterComponent>().front();
	auto position = manager_->get_component<PositionComponent>(entity);
	auto current_room = LevelSingleton::get_instance()->get_current_room();
	//right
	if(position->x >= 1250 && position->y >= 400 && position->y <= 800 && current_room->right != nullptr)
	{
		LevelSingleton::get_instance()->move_room_right();
		LevelSingleton::get_instance()->reload_level = true;
		position->x = 50;
	}
	//up
	else if(position->y <= 30 && position->x >= 448 && position->x <= 700 && current_room->top != nullptr)
	{
		LevelSingleton::get_instance()->move_room_up();
		LevelSingleton::get_instance()->reload_level = true;
		position->y = 800;
	}
	//left
	else if(position->x <= 30 && position->y >= 400 && position->y <= 800 && current_room->left != nullptr)
	{
		LevelSingleton::get_instance()->move_room_left();
		LevelSingleton::get_instance()->reload_level = true;
		position->x = 1230;
	}
	//down
	else if(position->y >= 930 && position->x >= 448 && position->x <= 700 && current_room->down != nullptr)
	{
		LevelSingleton::get_instance()->move_room_down();
		LevelSingleton::get_instance()->reload_level = true;
		position->y = 110;
	}
	
}