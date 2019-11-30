#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"
#include "EnemyComponent.h"

MoveSystem::MoveSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	//Get enemy characters
	auto enemies = manager_->get_all_entities_from_current_room<EnemyComponent>();
	if (!enemies.empty())
	{
		auto enemyEntity = enemies.front();
		for (auto enemyEntity : manager_->get_all_entities_from_current_room<EnemyComponent>())
		{
			auto entities = manager_->get_all_entities_from_current_room<CharacterComponent>();
			if (!entities.empty())
			{
				auto characterEntity = entities.front();
				auto enemyPosition = manager_->get_component<PositionComponent>(enemyEntity);
				auto enemyVelocity = manager_->get_component<VelocityComponent>(enemyEntity);
				auto playerPosition = manager_->get_component<PositionComponent>(characterEntity);
				if (playerPosition->x - enemyPosition->x > 0) {
					if (enemyVelocity->dx <= 0 ) {
						enemyVelocity->dx += enemyVelocity->deaceleration;
					}
				}
				else if (playerPosition->x - enemyPosition->x < 0) {
					if (enemyVelocity->dx >= 0) {
						enemyVelocity->dx -= enemyVelocity->deaceleration;
					}
				}
				else {
					enemyVelocity->dx -= enemyVelocity->deaceleration;
				}
				if (playerPosition->y - enemyPosition->y > 0) {
					if (enemyVelocity->dy <= 0) {
						enemyVelocity->dy += enemyVelocity->deaceleration;
					}
				}
				else if (playerPosition->y - enemyPosition->y < 0) {
					if (enemyVelocity->dy >= 0) {
						enemyVelocity->dy -= enemyVelocity->deaceleration;
					}
				}
				else {
					enemyVelocity->dy -= enemyVelocity->deaceleration;
				}
			}
		}

	}
	//Get player character
	auto entities = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (!entities.empty()) {
		auto characterEntity = entities.front();

		//Resolve velocity
		for (auto entity : manager_->get_all_entities_from_current_room<VelocityComponent>())
		{
			auto playerPosition = manager_->get_component<PositionComponent>(entity);

		auto velocity = manager_->get_component<VelocityComponent>(entity);
		playerPosition->x = playerPosition->x + velocity->dx;
		playerPosition->y = playerPosition->y + velocity->dy;
		if(velocity->dropOff != 0) {
			if (velocity->dx < 0) {
				velocity->dx = velocity->dx + velocity->dropOff > 0 ? 0 : velocity->dx + velocity->dropOff;
			}
			if (velocity->dx > 0) {
				velocity->dx = velocity->dx - velocity->dropOff < 0 ? 0 : velocity->dx - velocity->dropOff;
			}
			if (velocity->dy < 0) {
				velocity->dy = velocity->dy + velocity->dropOff > 0 ? 0 : velocity->dy + velocity->dropOff;
			}
			if (velocity->dy > 0) {
				velocity->dy = velocity->dy - velocity->dropOff < 0 ? 0 : velocity->dy - velocity->dropOff;
			}
		}

			if (characterEntity == entity) {
				velocity->dx = 0;
				velocity->dy = 0;
			}
		}
	}
}
