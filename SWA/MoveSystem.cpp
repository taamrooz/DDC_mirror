#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"
#include "EnemyComponent.h"
#include "SteeringBehaviors.h"
#include <QuadTree.h>
#include "TileComponent.h"
#include "CollisionComponent.h"
#include <Renderer.h>
#include <iostream>
#include <algorithm>


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
			std::shared_ptr<Engine::Node> node{ new Engine::Node{ Engine::Point{ x, y }, tile, collisionComponent->width, collisionComponent->height } };
			quadTree.insert(node);
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
		std::shared_ptr<Engine::Node> node{ new Engine::Node{ Engine::Point{ x - 150, y - 150 }, enemy, collisionComponent->width + 200, collisionComponent->height + 200 } };
		quadTree.insert(node);

	}


	//Get player character
	std::vector<std::tuple<std::shared_ptr<Engine::Node>, std::shared_ptr<Engine::Node>>> collisions = quadTree.get_collisions();
	auto vel = manager_->get_component<VelocityComponent>(enemyEnt);
	vel->steer_force = Pursuit(enemyEnt, player.front(), manager_) * 0.50;
	double dist = 1000000000.0;
	PositionComponent tilePos;
	vector2d start = vector2d();
	vector2d end = vector2d();
	vector2d diff = vector2d();
	for (auto const& node_tuple : collisions) {
		std::shared_ptr<Engine::Node> first_node = std::get<0>(node_tuple);
		std::shared_ptr<Engine::Node> second_node = std::get<1>(node_tuple);

		auto collisionComponent = manager_->get_component<CollisionComponent>(second_node->id);
		if (collisionComponent != nullptr) {
			auto enemyComponent = manager_->get_component<EnemyComponent>(first_node->id);
			auto tileComponent = manager_->get_component<TileComponent>(second_node->id);

			if (enemyComponent != nullptr && tileComponent != nullptr) {
				auto wallPos = manager_->get_component<PositionComponent>(second_node->id);
				auto enemyPos = manager_->get_component<PositionComponent>(first_node->id);

				auto enemyColl = manager_->get_component<CollisionComponent>(first_node->id);
				auto playerPos = manager_->get_component<PositionComponent>(player.front());

				vector2d vec1 = vector2d(wallPos->x, wallPos->y);
				vector2d vec2 = vector2d(wallPos->x + collisionComponent->width, wallPos->y);
				vector2d vec3 = vector2d(wallPos->x + collisionComponent->width, wallPos->y + collisionComponent->height);
				vector2d vec4 = vector2d(wallPos->x, wallPos->y + collisionComponent->height);
				vector2d enemyVec0 = vector2d(enemyPos->x + (enemyColl->width / 2), enemyPos->y + (enemyColl->height / 2));
				vector2d enemyVec1 = enemyVec0 + (normalize(vel->steer_force) * 150);

				Engine::set_render_draw_color(0, 255, 0, 255);

				if (intersects(enemyVec0, enemyVec1, vec1, vec2)) {
					vector2d oneY = vel->steer_force / vel->steer_force.y();
					int yDiff = wallPos->y - enemyVec0.y();
					vector2d collVector = oneY * yDiff;
					vector2d fullForce = normalize(vel->steer_force) * 150;
					vector2d rest = fullForce - collVector;
					if (length(collVector) < dist) {
						dist = length(collVector);
						start = vec1;
						end = vec2;
						if (playerPos->x > enemyPos->x) {
							//left
							vector2d down = normalize(vector2d(rest.y(), length(rest) * 5 * -1)) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(rest.y() * -1, length(rest) * 5 * -1)) * length(rest);
							diff = down;
						}
					}
				}
				if (intersects(enemyVec0, enemyVec1, vec2, vec3) && enemyVec0.x() != vec2.x()) {
					//Engine::render_line(wallPos->x + 64, wallPos->y, wallPos->x + 64, wallPos->y + tileComponent->height);
					vector2d oneX = vel->steer_force / vel->steer_force.x();
					int xDiff = wallPos->x + collisionComponent->width - enemyVec0.x();
					vector2d collVector = oneX * xDiff;
					vector2d fullForce = normalize(vel->steer_force) * 150;
					vector2d rest = fullForce - collVector;
					if (length(collVector) < dist && (enemyVec0 + collVector).y() != vec2.y()) {
						dist = length(collVector);
						start = vec2;
						end = vec3;
						if (playerPos->y > enemyPos->y) {
							//left
							vector2d down = normalize(vector2d(length(rest) * 5, rest.x() * -1)) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(length(rest) * 5, rest.x()) * length(rest));
							diff = down;
						}
					}
				}
				if (intersects(enemyVec0, enemyVec1, vec4, vec3)) {
					vector2d oneY = vel->steer_force / vel->steer_force.y();
					int yDiff = wallPos->y + collisionComponent->height - enemyVec0.y();
					vector2d collVector = oneY * yDiff;
					vector2d fullForce = normalize(vel->steer_force) * 150;
					vector2d rest = fullForce - collVector;

					if (length(collVector) < dist) {

						dist = length(collVector);
						start = vec4;
						end = vec3;
						if (playerPos->x > enemyPos->x) {
							//left
							vector2d down = normalize(vector2d(rest.y() * -1, length(rest) * 5)) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(rest.y(), length(rest) * 5)) * length(rest);
							diff = down;
							
						}
					}
				}
				if (intersects(enemyVec0, enemyVec1, vec4, vec1)) {
					//Engine::render_line(wallPos->x, wallPos->y, wallPos->x, wallPos->y + tileComponent->height);
					vector2d oneX = vel->steer_force / vel->steer_force.x();
					int xDiff = wallPos->x - enemyVec0.x();
					vector2d collVector = oneX * xDiff;
					vector2d fullForce = normalize(vel->steer_force) * 150;
					vector2d rest = fullForce - collVector;
					if (length(collVector) < dist) {
						dist = length(collVector);
						start = vec1;
						end = vec4;
						if (playerPos->y > enemyPos->y) {
							//left
							vector2d down = normalize(vector2d(length(rest) * 5 * -1, rest.x())) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(length(rest) * 5 * -1, rest.x() * -1)) * length(rest);
							diff = down;
						}
					}
				}
			}
		}
	}
	if (diff.x() != 0 || diff.y() != 0) {
		vel->steer_force = normalize(diff) * length(vel->steer_force);
	}
	

	auto pos = manager_->get_component<PositionComponent>(enemyEnt);
	//Engine::render_line(pos->x, pos->y, intersection.x(), intersection.y());
	Engine::set_render_draw_color(0, 255, 0, 255);
	Engine::render_line(pos->x, pos->y, pos->x + vel->steer_force.x() * 100, pos->y + vel->steer_force.y() * 100);
	Engine::render_line(start.x(), start.y(), end.x(), end.y());
	Engine::render_line(start.x(), start.y(), start.x() + diff.x(), start.y() + diff.y());

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

bool onLine(vector2d p1, vector2d p2, vector2d p) {   //check whether p is on the line or not
	if (p.x() <= std::max(p1.x(), p2.x()) && p.x() <= std::min(p1.x(), p2.x()) &&
		(p.y() <= std::max(p1.y(), p2.y()) && p.y() <= std::min(p1.y(), p2.y())))
		return true;

	return false;
}

int MoveSystem::direction(vector2d a, vector2d b, vector2d c)
{
	int val = (b.y() - a.y()) * (c.x() - b.x()) - (b.x() - a.x()) * (c.y() - b.y());
	if (val == 0)
		return 0;     //colinear
	else if (val < 0)
		return 2;    //anti-clockwise direction
	return 1;    //clockwise direction
}

bool MoveSystem::intersects(vector2d a1, vector2d a2, vector2d b1, vector2d b2)
{
	int dir1 = direction(a1, a2, b1);
	int dir2 = direction(a1, a2, b2);
	int dir3 = direction(b1, b2, a1);
	int dir4 = direction(b1, b2, a2);

	if (dir1 != dir2 && dir3 != dir4)
		return true; //they are intersecting

	if (dir1 == 0 && onLine(a1, a2, b1)) //when p2 of line2 are on the line1
		return true;

	if (dir2 == 0 && onLine(a1, a2, b2)) //when p1 of line2 are on the line1
		return true;

	if (dir3 == 0 && onLine(b1, b2, a1)) //when p2 of line1 are on the line2
		return true;

	if (dir4 == 0 && onLine(b1, b2, a2)) //when p1 of line1 are on the line2
		return true;

	return false;
}
