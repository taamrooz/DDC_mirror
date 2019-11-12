#include "CollisionHandlers.h"
#include "BaseSystem.h"
#include "CharacterComponent.h"
#include "DamagingComponent.h"
#include "HealthComponent.h"
#include <Renderer.h>
#include "AnimationComponent.h"
#include "ComponentFactory.h"
#include "ChestComponent.h"
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "VelocityComponent.h"

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

void ChestCollisionHandler(uint32_t entity1, uint32_t entity2, EntityManager* manager) {
	auto compFactory = ComponentFactory::get_instance();

	auto charC = manager->get_component<CharacterComponent>(entity2);
	if (charC != nullptr) {
		auto ani = manager->get_component<AnimationComponent>(entity1);
		ani->animations.at(ani->currentState).pause = false;
		

		//create drop
		int drop = manager->create_entity();
		auto chest = manager->get_component<ChestComponent>(entity1);
		ComponentFactory::get_instance()->CreateEntity(chest->contains, drop, manager);
		auto cPos = manager->get_component<PositionComponent>(entity1);
		auto cColl = manager->get_component<CollisionComponent>(entity1);
		auto pVel = manager->get_component<VelocityComponent>(entity2);
		auto dPos = std::make_unique<PositionComponent>(cPos->x + cColl->width / 2, cPos->y);
		auto dVel = std::make_unique<VelocityComponent>(pVel->dx, pVel->dy, 0.2);

		manager->add_component_to_entity(drop, std::move(dPos));
		manager->add_component_to_entity(drop, std::move(dVel));
		cColl->collisionHandler = nullptr;
		manager->remove_component_from_entity<ChestComponent>(entity1);

	}
}
