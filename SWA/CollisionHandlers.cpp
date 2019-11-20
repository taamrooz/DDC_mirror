#include "CollisionHandlers.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "RoomSingleton.h"
#include "LadderComponent.h"
#include "LevelBossComponent.h"
#include "LevelSingleton.h"

void DamageHandler(HealthComponent* health, DamagingComponent* dmg) {

	int currentTick = Engine::GetTicks();
	if (health->invulnerable_until < currentTick) {
		std::cout << "HIT" << std::endl;
		health->current_health -= dmg->damage_amount;
		health->invulnerable_until = health->time_invulnerable + currentTick;
	}
}

void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
	auto player = manager->get_component<CharacterComponent>(entity2);
	if (player == nullptr) {
		manager->remove_entity(entity1);
	}
}

void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager) {
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
			ani->lock_until = Engine::GetTicks() + 250;

			const auto health = manager->get_component<HealthComponent>(entity1);
			if (health != nullptr)
			{
				DamageHandler(health, dmg);
				if (health->current_health <= 0) {
					std::cout << "Game Over!" << std::endl;
				}
			}



		}
	}
}

void EnemyBulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager) {
	auto dmg = manager->get_component<DamagingComponent>(entity2);
	if (dmg != nullptr) {
		auto ani = manager->get_component<AnimationComponent>(entity1);
		ani->currentState = State::HIT;
		ani->lock_until = Engine::GetTicks() + 250;

		auto health = manager->get_component<HealthComponent>(entity1);
		DamageHandler(health, dmg);

		if (health->current_health <= 0) {
			manager->remove_entity(entity1);
		}
	}
}