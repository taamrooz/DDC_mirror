#include "CollisionHandlers.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "ladderComponent.h"
#include "RoomSingleton.h"
#include "LadderComponent.h"

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

void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
  //stop player from moving into a wall

	//take damage if entity2 has damagecomponent

	//etc.
  
	auto player = manager->get_component<CharacterComponent>(entity2);
	auto ladder = manager->get_component<LadderComponent>(entity1);

	if (ladder != nullptr) {
		// load next level
		if (!RoomSingleton::get_instance()->reload_room) {
			RoomSingleton::get_instance()->current_room_index++;
			RoomSingleton::get_instance()->reload_room = true;
		}
	} 
	
	auto dmg = manager->get_component<DamagingComponent>(entity2);
	if (dmg != nullptr) {
		auto ani = manager->get_component<AnimationComponent>(entity1);
		ani->currentState = State::HIT;
		ani->lock_until = Engine::GetTicks() + 250;

		auto health = manager->get_component<HealthComponent>(entity1);
		DamageHandler(health, dmg);
		
		if (health->current_health <= 0) {
			std::cout << "Game Over!" << std::endl;
		}
	}
}

void EnemyBulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
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