#include "SteeringBehaviors.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "TileComponent.h"
#include "CollisionComponent.h"
#include <QuadTree.h>
#include "EnemyComponent.h"
#include "CharacterComponent.h"
#include <Renderer.h>

using namespace Engine;

vector2d Wander()
{
	return vector2d(0, 0);
}

vector2d Seek(int entity, vector2d TargetPos, EntityManager<Component>* manager)
{
	auto pos = manager->get_component<PositionComponent>(entity);
	auto velocity = manager->get_component<VelocityComponent>(entity);
	vector2d DesiredVelocity = normalize(TargetPos - vector2d(pos->x, pos->y))
		* velocity->maxSpeed;
	return (DesiredVelocity - vector2d(velocity->dx, velocity->dy));
}

vector2d Flee(int entity, const int evader, EntityManager<Component>* manager)
{
	auto pos = manager->get_component<PositionComponent>(entity);
	auto evaderPos = manager->get_component<PositionComponent>(evader);
	auto evaderVelocity = manager->get_component<VelocityComponent>(entity);
	vector2d DesiredVelocity = normalize(vector2d(pos->x, pos->y) - vector2d(evaderPos->x, evaderPos->y))
		* evaderVelocity->maxSpeed;
	return (DesiredVelocity - vector2d(evaderVelocity->dx, evaderVelocity->dy));
}

vector2d Pursuit(int entity, const int evader, EntityManager<Component>* manager)
{
	auto loc = manager->get_component<PositionComponent>(entity);
	auto evaderLoc = manager->get_component<PositionComponent>(evader);
	auto velocity = manager->get_component<VelocityComponent>(entity);
	auto evaderVelocity = manager->get_component<VelocityComponent>(evader);

	vector2d heading = normalize(vector2d(velocity->dx, velocity->dy));
	vector2d evaderHeading = normalize(vector2d(evaderVelocity->dx, evaderVelocity->dy));
	vector2d evaderPos = vector2d(evaderLoc->x, evaderLoc->y);
	vector2d pos = vector2d(loc->x, loc->y);

	vector2d ToEvader = evaderPos - pos;
	double RelativeHeading = dot(heading, evaderHeading);
	if (dot(ToEvader, heading) > 0 && (RelativeHeading < -0.95)) //acos(0.95)=18 degs
	{
		return Seek(entity, evaderPos, manager);
	}
	//Not considered ahead so we predict where the evader will be.
	//the look-ahead time is proportional to the distance between the evader
	//and the pursuer; and is inversely proportional to the sum of the
	//agents' velocities
	double LookAheadTime = sqrt(pow(ToEvader.x(), 2) + pow(ToEvader.y(), 2)) / (velocity->maxSpeed + sqrt(pow(evaderVelocity->dy, 2) + pow(evaderVelocity->dx, 2)));
	//now seek to the predicted future position of the evader
	return Seek(entity, evaderPos + vector2d(evaderVelocity->dx, evaderVelocity->dy) * LookAheadTime, manager);
}

vector2d WallAvoidance(const int entity, EntityManager<Component>* manager) {
	
	auto enemies = manager->get_all_entities_from_current_room<EnemyComponent>();
	auto tiles = manager->get_all_entities_from_current_room<TileComponent>();

	auto player = manager->get_all_entities_from_current_room<CharacterComponent>();
	auto enemyEnt = enemies.front();


		double dist = 1000000000.0;
		PositionComponent tilePos;
		vector2d start = vector2d();
		vector2d end = vector2d();
		vector2d diff = vector2d();
		auto vel = manager->get_component<VelocityComponent>(entity);
		for (auto tile : tiles) {
			auto collisionComponent = manager->get_component<CollisionComponent>(tile);
			if (collisionComponent != nullptr) { //checks whether the tile is a wall
				auto enemyComponent = manager->get_component<EnemyComponent>(entity);
				auto tileComponent = manager->get_component<TileComponent>(tile);

				if (enemyComponent != nullptr && tileComponent != nullptr) {

					auto wallPos = manager->get_component<PositionComponent>(tile);
					auto enemyPos = manager->get_component<PositionComponent>(entity);

					auto enemyColl = manager->get_component<CollisionComponent>(entity);
					auto playerPos = manager->get_component<PositionComponent>(player.front());

					vector2d vec1 = vector2d(wallPos->x, wallPos->y);
					vector2d vec2 = vector2d(wallPos->x + collisionComponent->width, wallPos->y);
					vector2d vec3 = vector2d(wallPos->x + collisionComponent->width, wallPos->y + collisionComponent->height);
					vector2d vec4 = vector2d(wallPos->x, wallPos->y + collisionComponent->height);
					vector2d enemyVec0 = vector2d(enemyPos->x + (enemyColl->width / 2), enemyPos->y + (enemyColl->height / 2));
					vector2d enemyVec1 = enemyVec0 + (normalize(vel->steer_force) * 200);

					if (intersects(enemyVec0, enemyVec1, vec1, vec2)) {
						vector2d oneY = vel->steer_force / vel->steer_force.y();
						int yDiff = wallPos->y - enemyVec0.y();
						vector2d collVector = oneY * yDiff;
						vector2d fullForce = normalize(vel->steer_force) * 200;
						vector2d rest = fullForce - collVector;
						if (length(collVector) < dist) {
							dist = length(collVector);
							start = vec1;
							end = vec2;
							if (playerPos->x > enemyPos->x) {
								//left
								vector2d down = normalize(vector2d(rest.y(), length(rest) * -1)) * length(rest);
								diff = down;
							}
							else {
								vector2d down = normalize(vector2d(rest.y() * -1, length(rest) * -1)) * length(rest);
								diff = down;
							}
						}
					}
					if (intersects(enemyVec0, enemyVec1, vec2, vec3) && enemyVec0.x() != vec2.x()) {
						//Engine::render_line(wallPos->x + 64, wallPos->y, wallPos->x + 64, wallPos->y + tileComponent->height);
						vector2d oneX = vel->steer_force / vel->steer_force.x();
						int xDiff = wallPos->x + collisionComponent->width - enemyVec0.x();
						vector2d collVector = oneX * xDiff;
						vector2d fullForce = normalize(vel->steer_force) * 200;
						vector2d rest = fullForce - collVector;
						if (length(collVector) < dist) {
							dist = length(collVector);
							start = vec2;
							end = vec3;
							if (playerPos->y > enemyPos->y) {
								//left
								vector2d down = normalize(vector2d(length(rest) * 1, rest.x() * -1)) * length(rest);
								diff = down;
							}
							else {
								vector2d down = normalize(vector2d(length(rest) * 1, rest.x())) * length(rest);
								diff = down;
							}
						}
					}
					if (intersects(enemyVec0, enemyVec1, vec4, vec3)) {
						vector2d oneY = vel->steer_force / vel->steer_force.y();
						int yDiff = wallPos->y + collisionComponent->height - enemyVec0.y();
						vector2d collVector = oneY * yDiff;
						vector2d fullForce = normalize(vel->steer_force) * 200;
						vector2d rest = fullForce - collVector;

						if (length(collVector) < dist) {

							dist = length(collVector);
							start = vec4;
							end = vec3;
							if (playerPos->x > enemyPos->x) {
								//left
								vector2d down = normalize(vector2d(rest.y() * -1, length(rest) * 1)) * length(rest);
								diff = down;
							}
							else {
								vector2d down = normalize(vector2d(rest.y(), length(rest) * 1)) * length(rest);
								diff = down;

							}
						}
					}
					if (intersects(enemyVec0, enemyVec1, vec4, vec1)) {
						//Engine::render_line(wallPos->x, wallPos->y, wallPos->x, wallPos->y + tileComponent->height);
						vector2d oneX = vel->steer_force / vel->steer_force.x();
						int xDiff = wallPos->x - enemyVec0.x();
						vector2d collVector = oneX * xDiff;
						vector2d fullForce = normalize(vel->steer_force) * 200;
						vector2d rest = fullForce - collVector;
						if (length(collVector) < dist) {
							dist = length(collVector);
							start = vec1;
							end = vec4;
							if (playerPos->y > enemyPos->y) {
								//left
								vector2d down = normalize(vector2d(length(rest) * 1 * -1, rest.x())) * length(rest);
								diff = down;
							}
							else {
								vector2d down = normalize(vector2d(length(rest) * 1 * -1, rest.x() * -1)) * length(rest);
								diff = down;
							}
						}
					}
				}
			}

		}
		if (diff.x() != 0 || diff.y() != 0) {
			return (diff) * 0.07 + (vel->steer_force * 0.93);
		}
		return vel->steer_force;


	/*Engine::Point leftTop{ 0, 0 };
	Engine::Point botRight{ 1280, 960 }; // TODO: make this not hardcoded
	Engine::QuadTree quadTree{ leftTop, botRight };

	auto enemies = manager->get_all_entities_from_current_room<EnemyComponent>();
	auto tiles = manager->get_all_entities_from_current_room<TileComponent>();

	for (auto tile : tiles) {
		auto collisionComponent = manager->get_component<CollisionComponent>(tile);
		if (collisionComponent != nullptr) {
			auto positionComponent = manager->get_component<PositionComponent>(tile);

			int x = positionComponent->x;
			int y = positionComponent->y;
			std::shared_ptr<Engine::Node> node{ new Engine::Node{ Engine::Point{ x, y }, tile, collisionComponent->width, collisionComponent->height } };
			quadTree.insert(node);
		}
	}
	auto player = manager->get_all_entities_from_current_room<CharacterComponent>();
	auto enemyEnt = manager->get_all_entities_from_current_room<EnemyComponent>().front();
	for (auto enemy : enemies)
	{
		auto collisionComponent = manager->get_component<CollisionComponent>(enemy);
		auto positionComponent = manager->get_component<PositionComponent>(enemy);

		int x = positionComponent->x;
		int y = positionComponent->y;
		std::shared_ptr<Engine::Node> node{ new Engine::Node{ Engine::Point{ x + (collisionComponent->width / 2) - 200, y + (collisionComponent->height / 2) - 200 }, enemy, 400, 400 } };
		quadTree.insert(node);

	}

	std::vector<std::tuple<std::shared_ptr<Engine::Node>, std::shared_ptr<Engine::Node>>> collisions = quadTree.get_collisions();
	double dist = 1000000000.0;
	PositionComponent tilePos;
	vector2d start = vector2d();
	vector2d end = vector2d();
	vector2d diff = vector2d();
	auto vel = manager->get_component<VelocityComponent>(enemyEnt);
	for (auto const& node_tuple : collisions) {
		std::shared_ptr<Engine::Node> first_node = std::get<0>(node_tuple);
		std::shared_ptr<Engine::Node> second_node = std::get<1>(node_tuple);

		auto collisionComponent = manager->get_component<CollisionComponent>(second_node->id);
		if (collisionComponent != nullptr) {
			auto enemyComponent = manager->get_component<EnemyComponent>(first_node->id);
			auto tileComponent = manager->get_component<TileComponent>(second_node->id);

			if (enemyComponent != nullptr && tileComponent != nullptr) {
				
				auto wallPos = manager->get_component<PositionComponent>(second_node->id);
				auto enemyPos = manager->get_component<PositionComponent>(first_node->id);

				auto enemyColl = manager->get_component<CollisionComponent>(first_node->id);
				auto playerPos = manager->get_component<PositionComponent>(player.front());

				vector2d vec1 = vector2d(wallPos->x, wallPos->y);
				vector2d vec2 = vector2d(wallPos->x + collisionComponent->width, wallPos->y);
				vector2d vec3 = vector2d(wallPos->x + collisionComponent->width, wallPos->y + collisionComponent->height);
				vector2d vec4 = vector2d(wallPos->x, wallPos->y + collisionComponent->height);
				vector2d enemyVec0 = vector2d(enemyPos->x + (enemyColl->width / 2), enemyPos->y + (enemyColl->height / 2));
				vector2d enemyVec1 = enemyVec0 + (normalize(vel->steer_force) * 200);

				Engine::set_render_draw_color(0, 255, 0, 255);

				if (intersects(enemyVec0, enemyVec1, vec1, vec2)) {
					vector2d oneY = vel->steer_force / vel->steer_force.y();
					int yDiff = wallPos->y - enemyVec0.y();
					vector2d collVector = oneY * yDiff;
					vector2d fullForce = normalize(vel->steer_force) * 200;
					vector2d rest = fullForce - collVector;
					if (length(collVector) < dist) {
						dist = length(collVector);
						start = vec1;
						end = vec2;
						if (playerPos->x > enemyPos->x) {
							//left
							vector2d down = normalize(vector2d(rest.y(), length(rest) * -1)) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(rest.y() * -1, length(rest) * -1)) * length(rest);
							diff = down;
						}
					}
				}
				if (intersects(enemyVec0, enemyVec1, vec2, vec3) && enemyVec0.x() != vec2.x()) {
					//Engine::render_line(wallPos->x + 64, wallPos->y, wallPos->x + 64, wallPos->y + tileComponent->height);
					vector2d oneX = vel->steer_force / vel->steer_force.x();
					int xDiff = wallPos->x + collisionComponent->width - enemyVec0.x();
					vector2d collVector = oneX * xDiff;
					vector2d fullForce = normalize(vel->steer_force) * 200;
					vector2d rest = fullForce - collVector;
					if (length(collVector) < dist) {
						dist = length(collVector);
						start = vec2;
						end = vec3;
						if (playerPos->y > enemyPos->y) {
							//left
							vector2d down = normalize(vector2d(length(rest) * 1, rest.x() * -1)) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(length(rest) * 1, rest.x())) * length(rest);
							diff = down;
						}
					}
				}
				if (intersects(enemyVec0, enemyVec1, vec4, vec3)) {
					vector2d oneY = vel->steer_force / vel->steer_force.y();
					int yDiff = wallPos->y + collisionComponent->height - enemyVec0.y();
					vector2d collVector = oneY * yDiff;
					vector2d fullForce = normalize(vel->steer_force) * 200;
					vector2d rest = fullForce - collVector;

					if (length(collVector) < dist) {

						dist = length(collVector);
						start = vec4;
						end = vec3;
						if (playerPos->x > enemyPos->x) {
							//left
							vector2d down = normalize(vector2d(rest.y() * -1, length(rest) * 1)) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(rest.y(), length(rest) * 1)) * length(rest);
							diff = down;

						}
					}
				}
				if (intersects(enemyVec0, enemyVec1, vec4, vec1)) {
					//Engine::render_line(wallPos->x, wallPos->y, wallPos->x, wallPos->y + tileComponent->height);
					vector2d oneX = vel->steer_force / vel->steer_force.x();
					int xDiff = wallPos->x - enemyVec0.x();
					vector2d collVector = oneX * xDiff;
					vector2d fullForce = normalize(vel->steer_force) * 200;
					vector2d rest = fullForce - collVector;
					if (length(collVector) < dist) {
						dist = length(collVector);
						start = vec1;
						end = vec4;
						if (playerPos->y > enemyPos->y) {
							//left
							vector2d down = normalize(vector2d(length(rest) * 1 * -1, rest.x())) * length(rest);
							diff = down;
						}
						else {
							vector2d down = normalize(vector2d(length(rest) * 1 * -1, rest.x() * -1)) * length(rest);
							diff = down;
						}
					}
				}
			}
		}
	}
	if (diff.x() != 0 || diff.y() != 0) {
		return (diff) * 0.07 + (vel->steer_force * 0.93);
	}

	return vel->steer_force;*/
}

std::vector<vector2d> CreateFeelers(const int entity, EntityManager<Component>* manager) {

	std::vector<vector2d> m_Feelers;

	auto pos = manager->get_component<PositionComponent>(entity);
	auto velocity = manager->get_component<VelocityComponent>(entity);

	m_Feelers.push_back(normalize(vector2d(velocity->dx, velocity->dy)));
	m_Feelers.push_back(rotate(normalize(vector2d(velocity->dx, velocity->dy)), 45 * M_PI  / 180));
	m_Feelers.push_back(rotate(normalize(vector2d(velocity->dx, velocity->dy)), 315 * M_PI / 180));

	return m_Feelers;
}