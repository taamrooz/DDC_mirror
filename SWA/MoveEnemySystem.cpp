#include "MoveEnemySystem.h"
#include "EnemyComponent.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "SteeringBehaviors.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include "TileComponent.h"

MoveEnemySystem::MoveEnemySystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void MoveEnemySystem::update(double dt)
{
	Engine::Point leftTop{ 0, 0 };
	Engine::Point botRight{ 1280, 960 }; // TODO: make this not hardcoded
	Engine::QuadTree quadTree{ leftTop, botRight };

	auto tiles = manager_->get_all_entities_from_current_room<TileComponent>();

	for (auto tile : tiles) {
		auto collisionComponent = manager_->get_component<CollisionComponent>(tile);
		if (collisionComponent != nullptr) {
			auto positionComponent = manager_->get_component<PositionComponent>(tile);

			int x = positionComponent->x;
			int y = positionComponent->y;
			std::shared_ptr<Engine::Node> node{ new Engine::Node{ Engine::Point{ x, y }, tile, collisionComponent->width, collisionComponent->height } };
			quadTree.insert(node);
		}
	}

	auto enemies = manager_->get_all_entities_from_current_room<EnemyComponent>();
	auto player = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (!enemies.empty() && !player.empty()) {
		for (auto enemyEntity : enemies)
		{
			auto enemy = manager_->get_component<EnemyComponent>(enemyEntity);
			auto vel = manager_->get_component<VelocityComponent>(enemyEntity);
			auto pos = manager_->get_component<PositionComponent>(enemyEntity);
			auto coll = manager_->get_component<CollisionComponent>(enemyEntity);

			switch (enemy->state) {
			case Fleeing:
				vel->steer_force = Flee(enemyEntity, player.front(), manager_);
				break;
			case Pursuing:
				vel->steer_force = Pursuit(enemyEntity, player.front(), manager_);
				break;
			}

			std::shared_ptr<Engine::Node> node{ new Engine::Node{ Engine::Point{ pos->x + (coll->width / 2) - 150, pos->y + (coll->height / 2) - 150 }, enemyEntity, 300, 300 } };
			quadTree.insert(node);
			std::vector<std::tuple<std::shared_ptr<Engine::Node>, std::shared_ptr<Engine::Node>>> collisions = quadTree.get_collisions();
			vel->steer_force = WallAvoidance(enemyEntity, manager_, collisions);


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
