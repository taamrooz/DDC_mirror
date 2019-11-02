#include "CollisionHandlers.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "DamagingComponent.h"
#include "HealthComponent.h"
#include <Renderer.h>
#include "AnimationComponent.h"

void BulletCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
	auto player = manager->get_component<CharacterComponent>(entity2);
	if (player == nullptr) {
		manager->remove_entity(entity1);
	}
}

void PlayerCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager)
{
	auto dmg = manager->get_component<DamagingComponent>(entity2);
	if (dmg != nullptr) {
		int currentTick = Engine::GetTicks();
		auto health = manager->get_component<HealthComponent>(entity1);
		if (health->invulnerable_until < currentTick) {
			std::cout << "HIT" << std::endl;
			health->current_health -= dmg->damage_amount;
			health->invulnerable_until = health->time_invulnerable + Engine::GetTicks();
			auto ani = manager->get_component<AnimationComponent>(entity1);
			ani->currentState = State::HIT;
			ani->lock_until = currentTick + 250;
			if (health->current_health <= 0) {
				std::cout << "Game Over!" << std::endl;
			}
		}
		
	}
}
