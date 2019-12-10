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
#include "LevelSingleton.h"
#include "AnimationComponent.h"
#include <Renderer.h>
#include <Audio.h>

void DamageHandler(HealthComponent* health, DamagingComponent* dmg, EnemyComponent* enemy) {

	int currentTick = Engine::get_ticks();
	if (health->invulnerable_until < currentTick) {
		std::cout << "HIT" << std::endl;
		health->current_health -= dmg->damage_amount;
		health->invulnerable_until = health->time_invulnerable + currentTick;

		if (health->current_health < 3 && enemy != nullptr) {
			enemy->state = Fleeing;
		}
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

			if (boss_room->room_index == LevelSingleton::get_instance()->get_current_room_number()) {
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
					// load next room
					RoomSingleton::get_instance()->init_next_room();
					RoomSingleton::get_instance()->reload_room = true;
				}
			}
		}
		else {
			if (!RoomSingleton::get_instance()->reload_room) {
				// load next room
				RoomSingleton::get_instance()->init_next_room();
				RoomSingleton::get_instance()->reload_room = true;
			}
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
			DamageHandler(health, dmg, nullptr);
			if (health->current_health <= 0) {
				core->toggle_game_lost();
			}
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

			auto ani = manager->get_component<AnimationComponent>(entity1);
			auto texture = std::make_unique<TextureComponent>("flask_big_blue.png");
			manager->add_component_to_entity(entity1, std::move(texture));

			manager->remove_component_from_entity<CollisionComponent>(entity1);
			manager->remove_component_from_entity<AnimationComponent>(entity1);
			manager->remove_component_from_entity<PositionComponent>(entity1);
			manager->remove_component_from_entity<VelocityComponent>(entity1);
		}
	}
}

void EnemyCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core) {
	
	auto dmg = manager->get_component<DamagingComponent>(entity2);
	auto enemy = manager->get_component<EnemyComponent>(entity2);
	if (dmg != nullptr && enemy == nullptr) {
		auto ani = manager->get_component<AnimationComponent>(entity1);
		ani->currentState = State::HIT;
		ani->lock_until = Engine::get_ticks() + 250;

		auto health = manager->get_component<HealthComponent>(entity1);
		auto enemy = manager->get_component<EnemyComponent>(entity1);
		DamageHandler(health, dmg, enemy);

		if (health->current_health <= 0) {
			auto level_boss_component = manager->get_component<LevelBossComponent>(entity1);
			if (level_boss_component != nullptr) {
				manager->remove_component_from_entity<AnimationComponent>(entity1);
				manager->remove_component_from_entity<CollisionComponent>(entity1);
				manager->remove_component_from_entity<VelocityComponent>(entity1);
				Engine::stop_music();
				Engine::play_music("ingame.wav");
				core->toggle_game_won();
			}
			else {
				manager->remove_entity(entity1);
			}
		}
	}
	auto coll = manager->get_component<CollisionComponent>(entity2);
	if (coll != nullptr && coll->solid) {
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

void ChestCollisionHandler(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core) {
	auto compFactory = ComponentFactory::get_instance();

	auto charC = manager->get_component<CharacterComponent>(entity2);
	if (charC != nullptr) {
		auto ani = manager->get_component<AnimationComponent>(entity1);
		ani->animations.erase(ani->currentState);
		ani->animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::make_unique<Animation>(*Engine::load_animation("Animations/chest_empty_open.png", 3))));
		ani->animations.at(ani->currentState)->pause = false;
		ani->animations.at(ani->currentState)->loop = false;
		ani->animations.at(ani->currentState)->scale = 3;

		//create drop
		int drop = manager->create_entity();
		auto chest = manager->get_component<ChestComponent>(entity1);
		ComponentFactory::get_instance()->CreateEntity(chest->contains, drop, manager);
		auto cPos = manager->get_component<PositionComponent>(entity1);
		auto cColl = manager->get_component<CollisionComponent>(entity1);
		auto pVel = manager->get_component<VelocityComponent>(entity2);
		auto dPos = std::make_unique<PositionComponent>(cPos->x + cColl->width / 2 - 16, cPos->y);

		auto pPos = manager->get_component<PositionComponent>(entity2);
		auto pColl = manager->get_component<CollisionComponent>(entity2);
		int xv = pVel->dx;
		int yv = pVel->dy;
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
		manager->remove_component_from_entity<ChestComponent>(entity1);

	}
}
