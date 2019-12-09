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
			auto enemy = manager_->get_component<EnemyComponent>(enemyEntity);
			auto vel = manager_->get_component<VelocityComponent>(enemyEntity);
			auto pos = manager_->get_component<PositionComponent>(enemyEntity);

			switch (enemy->state) {
			case Fleeing :
				vel->steer_force = Flee(enemyEntity, player.front(), manager_);
				break;
			case Pursuing:
				vel->steer_force = Pursuit(enemyEntity, player.front(), manager_);
				break;
			}


			const vector2d acceleration = vel->steer_force / enemy->mass;
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
