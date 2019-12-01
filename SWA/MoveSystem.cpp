#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"
#include "EnemyComponent.h"
#include <vector2d.h>
#include "SteeringBehaviors.h"


MoveSystem::MoveSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	auto enemies = manager_->get_all_entities_from_current_room<EnemyComponent>();

	//Get player character
	auto player = manager_->get_all_entities_from_current_room<CharacterComponent>();

	if (!enemies.empty() && !player.empty()) {
		for (auto enemyEntity : enemies)
		{
			auto enemyMass = manager_->get_component<EnemyComponent>(enemyEntity);
			auto vel = manager_->get_component<VelocityComponent>(enemyEntity);
			auto pos = manager_->get_component<PositionComponent>(enemyEntity);
			vel->steer_force = WallAvoidance(player.front() , manager_);
			const vector2d acceleration = vel->steer_force / enemyMass->mass;
			vector2d velocity = vector2d(vel->dx, vel->dy);
			velocity += acceleration * dt;

			if (velocity.x() > vel->maxSpeed) {
				velocity = { trunc(vel->maxSpeed), velocity.y()};
			}
			if (velocity.y() > vel->maxSpeed) {
				velocity = { velocity.y(), trunc(vel->maxSpeed) };
			}
			vel->dx = velocity.x();
			vel->dy = velocity.y();
		}

	}
	//Get enemy characters
	/*auto enemies = manager_->get_all_entities_from_current_room<EnemyComponent>();
	if (!enemies.empty())
	{
		for (auto enemyEntity :enemies)
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

	}*/

	if (!player.empty()) {
		auto characterEntity = player.front();

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
