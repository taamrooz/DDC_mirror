#include "CollisionHandlers.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "RoomSingleton.h"
#include "LadderComponent.h"
#include "ComponentFactory.h"
#include "ChestComponent.h"
#include "InventoryComponent.h"
#include "TextureComponent.h"
#include "LevelBossComponent.h"
#include "DungeonSingleton.h"
#include "AnimationComponent.h"
#include <Renderer.h>
#include <Audio.h>
#include <algorithm>


void DamageHandler(uint32_t source, uint32_t target, Engine::EntityManager<Component>* manager, Core* core) {
	const auto health = manager->get_component<HealthComponent>(target);
	auto ani = manager->get_component<AnimationComponent>(target);
	auto dmg = manager->get_component<DamagingComponent>(source);
	auto enemy = manager->get_component<EnemyComponent>(target);
	auto player = manager->get_component<CharacterComponent>(target);
	int currentTick = Engine::get_ticks();
	if ( health != nullptr && health->invulnerable_until < currentTick) {
		health->current_health -= dmg->damage_amount;
		if (player != nullptr)
			Engine::play_audio("player_hit_sound.wav");
		else
			Engine::play_audio("enemy_hit_sound.wav");
		health->invulnerable_until = health->time_invulnerable + currentTick;

		ani->currentState = State::HIT;
		ani->lock_until = Engine::get_ticks() + 250;

		if (health->current_health < 3 && enemy != nullptr) {
			enemy->state = Fleeing;
		}
		if (health->current_health <= 0) {
			if (player != nullptr) {
				core->toggle_game_lost();
			}
			else if (enemy != nullptr) {
				auto level_boss_component = manager->get_component<LevelBossComponent>(target);
				if (level_boss_component != nullptr) {
					Engine::play_audio("boss_death_sound.wav");
					if (DungeonSingleton::get_instance()->is_last_dungeon())
					{
						Engine::stop_music();
						Engine::play_music("ingame.wav");
						core->toggle_game_won();
					}
				}
				else {
					Engine::play_audio("enemy_death_sound.wav");
				}
				manager->remove_entity(target);
			}
		}
	}
}

void PlayerBulletCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core) {
	auto player = manager->get_component<CharacterComponent>(entity2);
	if (player == nullptr) {		
		DamageHandler(entity1, entity2, manager, core);
		manager->remove_entity(entity1);
	}
}

void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core)
{
	//stop player from moving into a wall

	  //take damage if entity2 has damagecomponent

	  //etc.


	auto player = manager->get_component<CharacterComponent>(entity2);
	auto ladder = manager->get_component<LadderComponent>(entity1);

	if (player != nullptr && ladder != nullptr) {
		const auto boss_entities = manager->get_all_entities<LevelBossComponent>();
		bool all_bosses_dead = std::all_of(boss_entities.begin(), boss_entities.end(), [&manager](uint32_t entity)
			{
				return manager->get_component<HealthComponent>(entity)->current_health <= 0;
			});

		if (all_bosses_dead) {
			DungeonSingleton::get_instance()->move_dungeon_down(manager);
		}
	}
	
	auto coll = manager->get_component<CollisionComponent>(entity2);
	if (coll != nullptr && coll->solid) {
		UpdateVelocity(entity1, entity2, manager, core);
	}

}

void ItemCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core) {
	auto inv = manager->get_component<InventoryComponent>(entity2);
	if (inv != nullptr) {
		if (inv->items.size() < 10) {
			inv->items.push_back(entity1);
			auto texture = std::make_unique<TextureComponent>(std::unique_ptr<Texture>(Engine::load_tileset("flask_big_blue.png")), "flask_big_blue.png");

			manager->add_component_to_entity(entity1, std::move(texture));
			manager->remove_component_from_entity<CollisionComponent>(entity1);
			manager->remove_component_from_entity<AnimationComponent>(entity1);
			manager->remove_component_from_entity<RoomComponent>(entity1);
			manager->remove_component_from_entity<PositionComponent>(entity1);
			manager->remove_component_from_entity<VelocityComponent>(entity1);
		}
	}
}

void EnemyCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core) {
	auto enemy = manager->get_component<EnemyComponent>(entity2);
	if (enemy == nullptr) {
		DamageHandler(entity1, entity2, manager, core);
	}
	auto player = manager->get_component<CharacterComponent>(entity2);
	auto coll = manager->get_component<CollisionComponent>(entity2);
	if (coll != nullptr && coll->solid && enemy == nullptr) {
		UpdateVelocity(entity1, entity2, manager, core);
	}
}

void UpdateVelocity(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core)
{
	auto first_node_velocity_component = manager->get_component<VelocityComponent>(entity1);
	auto first_node_position_component = manager->get_component<PositionComponent>(entity1);
	auto first_node_collision_component = manager->get_component<CollisionComponent>(entity1);
	auto second_node_velocity_component = manager->get_component<VelocityComponent>(entity2);
	auto second_node_position_component = manager->get_component<PositionComponent>(entity2);
	auto second_node_collision_component = manager->get_component<CollisionComponent>(entity2);

	if (first_node_velocity_component != nullptr && second_node_velocity_component == nullptr) {
		int xDiff = 0;
		int yDiff = 0;
		int xd = 0;
		int yd = 0;
		if (first_node_velocity_component->dx != 0 && first_node_velocity_component->dy == 0) {
			if (first_node_position_component->y + first_node_collision_component->height >= second_node_position_component->y && first_node_position_component->y <= second_node_position_component->y + second_node_collision_component->height) {
				if (first_node_velocity_component->dx > 0) {
					xDiff = (first_node_position_component->x + first_node_collision_component->width - second_node_position_component->x);
					first_node_position_component->x -= xDiff;
					first_node_velocity_component->dx = 0;
				}
				else {
					xDiff = (first_node_position_component->x - (second_node_position_component->x + second_node_collision_component->width));
					first_node_position_component->x -= xDiff;
					first_node_velocity_component->dx = 0;
				}
			}
		}
		else if (first_node_velocity_component->dx == 0 && first_node_velocity_component->dy != 0) {
			if (first_node_position_component->x + first_node_collision_component->width >= second_node_position_component->x && first_node_position_component->x <= second_node_position_component->x + second_node_collision_component->width) {
				if (first_node_velocity_component->dy > 0) {
					yDiff = (first_node_position_component->y + first_node_collision_component->height - second_node_position_component->y);
					first_node_position_component->y -= yDiff;
					first_node_velocity_component->dy = 0;
				}
				else {
					yDiff = (first_node_position_component->y - (second_node_position_component->y + second_node_collision_component->height));
					first_node_position_component->y -= yDiff;
					first_node_velocity_component->dy = 0;
				}
			}
		}
		else {
			if (first_node_velocity_component->dx > 0) {
				xDiff = (first_node_position_component->x + first_node_collision_component->width - second_node_position_component->x);
				xd = xDiff / first_node_velocity_component->dx;
				xDiff++;
			}
			if (first_node_velocity_component->dx < 0) {
				//diff between xpos and collision xpos;
				xDiff = (first_node_position_component->x - (second_node_position_component->x + second_node_collision_component->width));
				xd = xDiff / first_node_velocity_component->dx;
				xDiff--;
			}
			if (first_node_velocity_component->dy > 0) {
				yDiff = (first_node_position_component->y + first_node_collision_component->height - second_node_position_component->y);
				yd = yDiff / first_node_velocity_component->dy;
				yDiff++;
			}
			if (first_node_velocity_component->dy < 0) {
				yDiff = (first_node_position_component->y - (second_node_position_component->y + second_node_collision_component->height));
				yd = yDiff / first_node_velocity_component->dy;
				yDiff--;
			}
			if (xd < yd) {
				first_node_position_component->x -= xDiff;
				first_node_velocity_component->dx = 0;
			}
			if (xd > yd) {
				first_node_position_component->y -= yDiff;
				first_node_velocity_component->dy = 0;
			}
		}
	}
	if (first_node_velocity_component != nullptr && second_node_velocity_component != nullptr) {
		if ((second_node_position_component->x >= first_node_position_component->x + first_node_collision_component->width && first_node_velocity_component->dx >= 0)
			|| (second_node_position_component->x + second_node_collision_component->width <= first_node_position_component->x && first_node_velocity_component->dx <= 0)) {
			second_node_velocity_component->dx = first_node_velocity_component->dx;
		}
		if ((second_node_position_component->y >= first_node_position_component->y + first_node_collision_component->height && first_node_velocity_component->dy >= 0)
			|| (second_node_position_component->y + second_node_collision_component->height <= first_node_position_component->y && first_node_velocity_component->dy <= 0)) {
			second_node_velocity_component->dy = first_node_velocity_component->dy;
		}
	}
}

void ChestCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core) {
	auto compFactory = ComponentFactory::get_instance();

	auto charC = manager->get_component<CharacterComponent>(entity2);
	if (charC != nullptr) {
		auto ani = manager->get_component<AnimationComponent>(entity1);
		ani->animations.erase(ani->currentState);
		ani->animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::unique_ptr<Animation>(Engine::load_animation("Animations/chest_empty_open.png", 3))));
		ani->state_to_frames.erase(ani->currentState);
		ani->state_to_frames.emplace(State::DEFAULT, 3);
		ani->state_to_path.erase(ani->currentState);
		ani->state_to_path.emplace(State::DEFAULT, "Animations/chest_empty_open.png");
		ani->animations.at(ani->currentState)->pause = false;
		ani->animations.at(ani->currentState)->loop = false;
		ani->animations.at(ani->currentState)->scale = 3;

		//create drop
		int drop = manager->create_entity();
		auto chest = manager->get_component<ChestComponent>(entity1);
		auto room = manager->get_component<RoomComponent>(entity1);
		ComponentFactory::get_instance()->CreateEntity(chest->contains, drop, manager, room);
		auto cPos = manager->get_component<PositionComponent>(entity1);
		auto cColl = manager->get_component<CollisionComponent>(entity1);
		auto pVel = manager->get_component<VelocityComponent>(entity2);
		auto dPos = std::make_unique<PositionComponent>(cPos->x + cColl->width / 2 - 16, cPos->y);

		auto pPos = manager->get_component<PositionComponent>(entity2);
		auto pColl = manager->get_component<CollisionComponent>(entity2);
		int xv = 0;
		int yv = 0;
		if (pPos->x >= cPos->x + cColl->width) {
			xv = -5;
		}
		else if (pPos->x + pColl->width <= cPos->x) {
			xv = 5;
		}
		else if (pPos->y > cPos->y) {
			yv = -5;
		}
		else {
			yv = 5;
		}
		auto dVel = std::make_unique<VelocityComponent>(xv, yv, 0.2);

		manager->add_component_to_entity(drop, std::move(dPos));
		manager->add_component_to_entity(drop, std::move(dVel));
		cColl->collisionHandler = nullptr;
		cColl->function_name = CollisionHandlerNames::None;
		manager->remove_component_from_entity<ChestComponent>(entity1);
		Engine::play_audio("chest_open.wav");
	}
}


CollisionHandlers::CollisionHandlers()
{
	name_function_map_.try_emplace(CollisionHandlerNames::None, nullptr);
	name_function_map_.try_emplace(CollisionHandlerNames::PlayerBulletCollisionHandler, PlayerBulletCollisionHandler);
	name_function_map_.try_emplace(CollisionHandlerNames::PlayerCollisionHandler, PlayerCollisionHandler);
	name_function_map_.try_emplace(CollisionHandlerNames::ItemCollisionHandler, ItemCollisionHandler);
	name_function_map_.try_emplace(CollisionHandlerNames::ChestCollisionHandler, ChestCollisionHandler);
	name_function_map_.try_emplace(CollisionHandlerNames::EnemyCollisionHandler, EnemyCollisionHandler);
	name_function_map_.try_emplace(CollisionHandlerNames::UpdateVelocity, UpdateVelocity);
}

std::function<void(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component> * manager, Core * core)>
CollisionHandlers::GetFunction(CollisionHandlerNames name)
{
	auto find_return = name_function_map_.find(name);
	return find_return->second;
}
