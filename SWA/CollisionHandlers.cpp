#include "CollisionHandlers.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "RoomSingleton.h"
#include "LadderComponent.h"
#include "LevelBossComponent.h"
#include "LevelSingleton.h"
#include "AnimationComponent.h"
#include <Renderer.h>

void DamageHandler(HealthComponent* health, DamagingComponent* dmg) {

	int currentTick = Engine::get_ticks();
	if (health->invulnerable_until < currentTick) {
		std::cout << "HIT" << std::endl;
		health->current_health -= dmg->damage_amount;
		health->invulnerable_until = health->time_invulnerable + currentTick;
	}
}

void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core)
{
	auto player = manager->get_component<CharacterComponent>(entity2);
	if (player == nullptr) {
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
		const auto boss_entities = manager->get_all_entities_from_current_room<LevelBossComponent>();
		bool is_boss_room = !boss_entities.empty();

		if (is_boss_room) {
			const auto boss_entity = boss_entities.front();
			const auto boss_health = manager->get_component<HealthComponent>(boss_entity);
			const auto boss_room = manager->get_component<RoomComponent>(boss_entity);

			/* rewrite this!! */
			if (boss_room->room_name.compare(RoomSingleton::get_instance()->get_current_room_name()) == 0) {
				// current room is where levelBoss is living
				if (boss_health->current_health <= 0) {
					if (!LevelSingleton::get_instance()->reload_level) {
						LevelSingleton::get_instance()->init_next_level();
						LevelSingleton::get_instance()->reload_level = true;
					}
				}
			}
			else {
				if (!RoomSingleton::get_instance()->reload_room) {
					// load next level
					RoomSingleton::get_instance()->init_next_room();
					RoomSingleton::get_instance()->reload_room = true;
				}
			}
		}
		else {
			if (!RoomSingleton::get_instance()->reload_room) {
				// load next level
				RoomSingleton::get_instance()->init_next_room();
				RoomSingleton::get_instance()->reload_room = true;
			}
		}

		auto dmg = manager->get_component<DamagingComponent>(entity2);
		auto ani = manager->get_component<AnimationComponent>(entity1);
		if (dmg != nullptr && ani != nullptr) {

			ani->currentState = State::HIT;
			ani->lock_until = Engine::get_ticks() + 250;

			const auto health = manager->get_component<HealthComponent>(entity1);
			if (health != nullptr)
			{
				DamageHandler(health, dmg);
				if (health->current_health <= 0) {
					core->toggle_game_lost();
				}
			}



		}

		UpdateVelocity(entity1, entity2, manager, core);
	}
}

void EnemyBulletCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core)
{
	auto dmg = manager->get_component<DamagingComponent>(entity2);
	if (dmg != nullptr) {
		auto ani = manager->get_component<AnimationComponent>(entity1);
		ani->currentState = State::HIT;
		ani->lock_until = Engine::get_ticks() + 250;

		auto health = manager->get_component<HealthComponent>(entity1);
		DamageHandler(health, dmg);

		if (health->current_health <= 0) {
			manager->remove_entity(entity1);
			core->toggle_game_won();
		}
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

	if (first_node_velocity_component != nullptr) {
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
				xDiff = (first_node_position_component->x + first_node_collision_component->width - second_node_position_component->x) + 1;
				xd = xDiff / first_node_velocity_component->dx;
			}
			if (first_node_velocity_component->dx < 0) {
				//diff between xpos and collision xpos;
				xDiff = (first_node_position_component->x - (second_node_position_component->x + second_node_collision_component->width)) - 1;
				xd = xDiff / first_node_velocity_component->dx;
			}
			if (first_node_velocity_component->dy > 0) {
				yDiff = (first_node_position_component->y + first_node_collision_component->height - second_node_position_component->y) + 1;
				yd = yDiff / first_node_velocity_component->dy;
			}
			if (first_node_velocity_component->dy < 0) {
				yDiff = (first_node_position_component->y - (second_node_position_component->y + second_node_collision_component->height)) - 1;
				yd = yDiff / first_node_velocity_component->dy;
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
}
