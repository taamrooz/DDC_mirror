#include "CheatSystem.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "KeyBindingSingleton.h"
#include "HealthComponent.h"
#include <Audio.h>
#include "LevelBossComponent.h"
#include "Core.h"

CheatSystem::CheatSystem(Engine::EntityManager<Component>* manager, Core& core) : BaseSystem(manager), core_(&core) {}

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
			else if (i.first == KeyBindingSingleton::get_instance()->get_next_room_key())
			{
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_left_key())) DungeonSingleton::get_instance()->move_room_left();
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_up_key())) DungeonSingleton::get_instance()->move_room_up();
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_right_key())) DungeonSingleton::get_instance()->move_room_right();
				if (KeyBindingSingleton::get_instance()->is_key_down(KeyBindingSingleton::get_instance()->get_move_down_key())) DungeonSingleton::get_instance()->move_room_down();
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_kill_all_key())
			{
				auto h_entities = manager_->get_all_entities_from_current_room<HealthComponent>();
				for (auto h_entity : h_entities)
				{
					if (h_entity == entity) continue;
					manager_->remove_entity(h_entity);
				}

				const auto boss_entities = manager_->get_all_entities<LevelBossComponent>();
				bool all_bosses_dead = std::all_of(boss_entities.begin(), boss_entities.end(), [this](uint32_t entity)
					{
						return manager_->get_component<HealthComponent>(entity)->current_health <= 0;
					});

				if (DungeonSingleton::get_instance()->is_last_dungeon() && all_bosses_dead)
				{
					Engine::stop_music();
					Engine::play_music("ingame.wav");
					core_->toggle_game_won();
				}
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_gamespeed_increase())
			{
				core_->gamespeed_increase();
			}
			else if (i.first == KeyBindingSingleton::get_instance()->get_gamespeed_decrease())
			{
				core_->gamespeed_decrease();
			}
		}
	}
}
