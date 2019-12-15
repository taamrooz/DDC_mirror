#include "MoveEnemySystem.h"
#include "EnemyComponent.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "SteeringBehaviors.h"
#include "CharacterComponent.h"

MoveEnemySystem::MoveEnemySystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void MoveEnemySystem::update(double dt)
{
	auto enemies = manager_->get_all_entities_from_current_room<EnemyComponent>();
	auto player = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (!enemies.empty() && !player.empty()) {
		for (auto enemyEntity : enemies)
		{
			
			auto enemy = manager_->get_component<EnemyComponent>(enemyEntity);
			auto vel = manager_->get_component<VelocityComponent>(enemyEntity);
			auto pos = manager_->get_component<PositionComponent>(enemyEntity);
			if (vel->dx == 0 && vel->dy == 0) {
				int k = 0;
			}
			switch (enemy->state) {
			case Fleeing:
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
				velocity = { trunc(vel->maxSpeed), velocity.y() };
			}
			if (velocity.y() > vel->maxSpeed) {
				velocity = { velocity.y(), trunc(vel->maxSpeed) };
			}
			vel->dx = velocity.x();
			vel->dy = velocity.y();
		}

	}
}
