#include "CheatSystem.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "KeyBindingSingleton.h"
#include "HealthComponent.h"
#include <Audio.h>
#include "LevelBossComponent.h"

CheatSystem::CheatSystem(Engine::EntityManager<Component>* manager, Core& core) : BaseSystem(manager)
{
	CheatSystem::core = &core;
}

void CheatSystem::update(double dt)
{
	auto entities = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (entities.empty()) return;
	auto entity = entities.front();
	auto health = manager_->get_component<HealthComponent>(entity);
	auto velocity = manager_->get_component<VelocityComponent>(entity);
	auto position = manager_->get_component<PositionComponent>(entity);
	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.second) {
			if (i.first == KeyBindingSingleton::get_instance()->get_speedhack_key()) {
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_left_key())) velocity->dx -= 10;
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_up_key())) velocity->dy -= 10;
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_right_key())) velocity->dx += 10;
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_down_key())) velocity->dy += 10;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_invincible_key())
			{
				health->current_health = health->max_health;
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_teleport_key())
			{
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_left_key())) position->x -= 50;
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_up_key())) position->y -= 50;
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_right_key())) position->x += 50;
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_down_key())) position->y += 50;
			}
			else if(i.first == KeyBindingSingleton::get_instance()->get_next_room_key())
			{
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_left_key())) DungeonSingleton::get_instance()->move_room_left();
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_up_key())) DungeonSingleton::get_instance()->move_room_up();
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_right_key())) DungeonSingleton::get_instance()->move_room_right();
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_down_key())) DungeonSingleton::get_instance()->move_room_down();
			}
			else if(i.first == KeyBindingSingleton::get_instance()->get_kill_all_key())
			{
				auto h_entities = manager_->get_all_entities_from_current_room<HealthComponent>();
				for (auto h_entity : h_entities)
				{
					if (h_entity == entity) continue;
					manager_->remove_entity(h_entity);
				}

				bool all_bosses_are_dead = true;
				const auto boss_entities = manager_->get_all_entities<LevelBossComponent>();
				for (auto i = boss_entities.begin(); i != boss_entities.end(); ++i) {
					if (manager_->get_component<HealthComponent>(*i)->current_health > 0) {
						all_bosses_are_dead = false;
						break;
					}
				}

				if (DungeonSingleton::get_instance()->is_last_dungeon() && all_bosses_are_dead)
				{
					Engine::stop_music();
					Engine::play_music("ingame.wav");
					core->toggle_game_won();
				}
			}
		}
	}
}
