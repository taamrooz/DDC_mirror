#include "RoomSystem.h"
#include "TileComponent.h"
#include "RoomSingleton.h"
#include "PositionComponent.h"
#include "ComponentFactory.h"
#include "CollisionHandlers.h"
#include "DungeonSingleton.h"
#include <Audio.h>
#include "LevelBossComponent.h"
#include "CharacterComponent.h"

RoomSystem::RoomSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager)
{}

void RoomSystem::update(double dt)
{
	if (RoomSingleton::get_instance()->reload_room)
	{					
		auto room_entities = manager_->get_all_entities_from_current_room<PositionComponent>();
		auto tiles = manager_->get_all_entities<TileComponent>();
		for (auto tile : tiles)
		{
			manager_->remove_entity(tile);
		}
		if (room_entities.empty())
		{		
			DungeonSingleton::get_instance()->load_room(manager_);
		}else
		{
			DungeonSingleton::get_instance()->load_tiles(manager_);
		}
		auto player = manager_->get_all_entities<CharacterComponent>();
		if (!player.empty())
		{
			auto player_room = manager_->get_component<RoomComponent>(player.front());
			player_room->room_index = DungeonSingleton::get_instance()->get_current_room_number();
		}
		else
		{
			auto player_id = manager_->create_entity();
			ComponentFactory::get_instance()->CreateEntity("player", player_id, manager_);
			auto pos = std::make_unique<PositionComponent>(650, 500);
			manager_->add_component_to_entity(player_id, std::move(pos));
		}
		RoomSingleton::get_instance()->reload_room = false;

		const auto boss_entities = manager_->get_all_entities_from_current_room<LevelBossComponent>();
		if (!boss_entities.empty()) {
			Engine::stop_music();
			Engine::play_music("danger.wav");
		}
	}
	auto entity = manager_->get_all_entities_from_current_room<CharacterComponent>().front();
	auto position = manager_->get_component<PositionComponent>(entity);
	auto current_room = DungeonSingleton::get_instance()->get_current_room();
	//right
	if (position->x >= 1250 && position->y >= 400 && position->y <= 800 && current_room->right != nullptr)
	{
		DungeonSingleton::get_instance()->move_room(right);
		position->x = 50;
	}
	//up
	else if (position->y <= 30 && position->x >= 448 && position->x <= 700 && current_room->top != nullptr)
	{
		DungeonSingleton::get_instance()->move_room(up);
		position->y = 800;
	}
	//left
	else if (position->x <= 30 && position->y >= 400 && position->y <= 800 && current_room->left != nullptr)
	{
		DungeonSingleton::get_instance()->move_room(left);
		position->x = 1230;
	}
	//down
	else if (position->y >= 930 && position->x >= 448 && position->x <= 700 && current_room->down != nullptr)
	{
		DungeonSingleton::get_instance()->move_room(down);
		position->y = 110;
	}

}