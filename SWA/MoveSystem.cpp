#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"
#include "EnemyComponent.h"
#include <vector2d.h>
#include "SteeringBehaviors.h"
#include <QuadTree.h>
#include "TileComponent.h"
#include "CollisionComponent.h"
#include <Renderer.h>


MoveSystem::MoveSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	Engine::Point leftTop{ 0, 0 };
	Engine::Point botRight{ 1280, 960 }; // TODO: make this not hardcoded
	Engine::QuadTree quadTree{ leftTop, botRight };

	auto enemies = manager_->get_all_entities_from_current_room<EnemyComponent>();
	auto tiles = manager_->get_all_entities_from_current_room<TileComponent>();

	for (auto tile : tiles) {
		auto collisionComponent = manager_->get_component<CollisionComponent>(tile);
		if (collisionComponent != nullptr) {
			auto positionComponent = manager_->get_component<PositionComponent>(tile);

			int x = positionComponent->x;
			int y = positionComponent->y;

			quadTree.insert(new Engine::Node{ Engine::Point{ x, y }, tile, collisionComponent->width, collisionComponent->height });
		}
	}
	auto player = manager_->get_all_entities_from_current_room<CharacterComponent>();
	auto enemyEnt = manager_->get_all_entities_from_current_room<EnemyComponent>().front();
	for (auto enemy : enemies)
	{
		auto collisionComponent = manager_->get_component<CollisionComponent>(enemy);
		auto positionComponent = manager_->get_component<PositionComponent>(enemy);

		int x = positionComponent->x;
		int y = positionComponent->y;

		quadTree.insert(new Engine::Node{ Engine::Point{ x - 150, y - 150 }, enemy, collisionComponent->width + 200, collisionComponent->height + 200 });
		auto vel = manager_->get_component<VelocityComponent>(enemy);

	}


	//Get player character
	std::vector<std::tuple<Engine::Node*, Engine::Node*>> collisions = quadTree.get_collisions();
	int i = 0;
	int j = 0;
	auto vel = manager_->get_component<VelocityComponent>(enemyEnt);
	vel->steer_force = Pursuit(enemyEnt, player.front(), manager_);
	double dist = 1000000000.0;
	vector2d shortest = vector2d();
	PositionComponent tilePos;
	vector2d enemyVec = normalize(vel->steer_force);
	for (auto const& node_tuple : collisions) {
		Engine::Node* first_node = std::get<0>(node_tuple);
		Engine::Node* second_node = std::get<1>(node_tuple);
		auto collisionComponent = manager_->get_component<CollisionComponent>(second_node->id);
		if (collisionComponent != nullptr) {
			auto enemyComponent = manager_->get_component<EnemyComponent>(first_node->id);
			auto tileComponent = manager_->get_component<TileComponent>(second_node->id);

			if (enemyComponent != nullptr && tileComponent != nullptr) {
				auto wallPos = manager_->get_component<PositionComponent>(second_node->id);
				auto enemyPos = manager_->get_component<PositionComponent>(first_node->id);

				auto enemyColl = manager_->get_component<CollisionComponent>(first_node->id);
				auto playerPos = manager_->get_component<PositionComponent>(player.front());

				vector2d vec1 = normalize(vector2d(wallPos->x + tileComponent->width - enemyPos->x, (wallPos->y - enemyPos->y)));
				vector2d vec2 = normalize(vector2d(wallPos->x - enemyPos->x, (wallPos->y + tileComponent->height) - enemyPos->y));
				vector2d vec3 = normalize(vector2d(wallPos->x - enemyPos->x, wallPos->y - enemyPos->y));
				vector2d vec4 = normalize(vector2d(wallPos->x + tileComponent->width - enemyPos->x, wallPos->y + tileComponent->height - enemyPos->y));
				Engine::render_line(wallPos->x + tileComponent->width, wallPos->y, wallPos->x, wallPos->y + tileComponent->height);
				Engine::render_line(wallPos->x, wallPos->y, wallPos->x + tileComponent->width, wallPos->y + tileComponent->height);
				Engine::set_render_draw_color(255, 255, 255, 255);
				Engine::set_render_draw_color(0, 255, 0, 255);

				if ((enemyVec.x() <= vec1.x() && enemyVec.x() >= vec2.x() && enemyVec.y() >= vec1.y() && enemyVec.y() <= vec2.y()) ||
					(enemyVec.x() >= vec1.x() && enemyVec.x() <= vec2.x() && enemyVec.y() <= vec1.y() && enemyVec.y() >= vec2.y()) ||
					(enemyVec.x() >= vec3.x() && enemyVec.x() <= vec4.x() && enemyVec.y() >= vec3.y() && enemyVec.y() <= vec4.y()) ||
					(enemyVec.x() <= vec3.x() && enemyVec.x() >= vec4.x() && enemyVec.y() <= vec3.y() && enemyVec.y() >= vec4.y())) {
					vector2d wallVector = vector2d(((enemyPos->x + enemyColl->width) - wallPos->x), 1);
					if (length(vector2d(wallPos->x - enemyPos->x, wallPos->y - enemyPos->y)) < dist) {
						dist = length(vector2d(wallPos->x - enemyPos->x, wallPos->y - enemyPos->y));

						tilePos = *wallPos;
						shortest = vector2d(wallPos->x + tileComponent->width - enemyPos->x, wallPos->y + tileComponent->height - enemyPos->y);
					}
				}
			}
		}
	}

	//Todo: calculate steer force
	Engine::draw_rectangle(rect2d(tilePos.x, tilePos.y, 64, 64));
	//vector2d desiredVel = perp(vel->steer_force);
	auto pos = manager_->get_component<PositionComponent>(enemyEnt);
	//if (pos->x > tilePos.x) {
	//	desiredVel = vector2d(desiredVel.x() * -1, desiredVel.y());
	//}
	//if (pos->y > tilePos.y) {
	//	desiredVel = vector2d(desiredVel.x(), desiredVel.y() * -1);
	//}

	//vel->steer_force += desiredVel;
	vector2d overshoot = (normalize(vel->steer_force) * 150) - shortest;
	//vector2d desiredForce = vector2d(tilePos.x, tilePos.y + 64 + (diff * -1));
	//vector2d desiredVel = normalize(desiredForce - vector2d(pos->x, pos->y)) * 20;
	vector2d target = vector2d();
	double distance = 100000.0;
	if (tilePos.x != 0) {
		if (length(vector2d(tilePos.x + 32 - pos->x, tilePos.y - pos->y)) < distance) {
			//top
			distance = length(vector2d(tilePos.x + 32 - pos->x, tilePos.y - pos->y));
			if (vel->steer_force.x() < 0) {
				target = vector2d(length(vel->steer_force) * -1, 0);
			}
			else {
				target = vector2d(length(vel->steer_force), 0);
			}
		}
		if (length(vector2d(tilePos.x - pos->x, tilePos.y + 32 - pos->y)) < distance) {
			//left
			distance = length(vector2d(tilePos.x - pos->x, tilePos.y + 32 - pos->y));
			if (vel->steer_force.y() < 0) {
				target = vector2d(0, length(vel->steer_force) * -1);
			}
			else {
				target = vector2d(0, length(vel->steer_force));
			}
		}
		if (length(vector2d(tilePos.x + 64 - pos->x, tilePos.y + 32 - pos->y)) < distance) {
			//right
			distance = length(vector2d(tilePos.x + 64 - pos->x, tilePos.y + 32 - pos->y));

			if (vel->steer_force.y() < 0) {
				target = vector2d(0, length(vel->steer_force) * -1);
			}
			else {
				target = vector2d(0, length(vel->steer_force));
			}

		}
		if (length(vector2d(tilePos.x + 32 - pos->x, tilePos.y + 64 - pos->y)) < distance) {
			//bot
			distance = length(vector2d(tilePos.x + 32 - pos->x, tilePos.y + 64 - pos->y));

			if (vel->steer_force.x() < 0) {
				target = vector2d(length(vel->steer_force) * -1, 0);
			}
			else {
				target = vector2d(length(vel->steer_force), 0);
			}

		}
		vel->steer_force = target;
	}

	Engine::render_line(pos->x, pos->y, pos->x + vel->steer_force.x() * 100, pos->y + vel->steer_force.y() * 100);


	if (!enemies.empty() && !player.empty()) {
		for (auto enemyEntity : enemies)
		{

			auto enemyMass = manager_->get_component<EnemyComponent>(enemyEntity);
			auto vel = manager_->get_component<VelocityComponent>(enemyEntity);
			auto pos = manager_->get_component<PositionComponent>(enemyEntity);

			const vector2d acceleration = vel->steer_force / enemyMass->mass;
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
			if (velocity->dropOff != 0) {
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
