#include "SteeringBehaviors.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "TileComponent.h"
#include "CollisionComponent.h"
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

vector2d WallAvoidance(const int entity, EntityManager<Component>* manager, std::vector<std::tuple<std::shared_ptr<Engine::Node>, std::shared_ptr<Engine::Node>>> collisions) {

	auto player = manager->get_all_entities_from_current_room<CharacterComponent>();
	auto playerPos = manager->get_component<PositionComponent>(player.front());
	auto enemyPos = manager->get_component<PositionComponent>(entity);
	auto enemyColl = manager->get_component<CollisionComponent>(entity);

	double dist = 10000.0;
	vector2d diff = vector2d();
	auto vel = manager->get_component<VelocityComponent>(entity);

	const vector2d enemyVec0 = vector2d(enemyPos->x + (enemyColl->width / 2), enemyPos->y + (enemyColl->height / 2));
	const vector2d enemyVec1 = enemyVec0 + (normalize(vel->steer_force) * 200);
	const vector2d collRange = normalize(vel->steer_force) * 200;
	const vector2d oneX = vel->steer_force / vel->steer_force.x();
	const vector2d oneY = vel->steer_force / vel->steer_force.y();
	auto enemyComponent = manager->get_component<EnemyComponent>(entity);

	for (auto const& node_tuple : collisions) {
		const int tile = std::get<1>(node_tuple)->id;
		auto tileComponent = manager->get_component<TileComponent>(tile);

		if (entity == std::get<0>(node_tuple)->id && tileComponent != nullptr) {
			//Engine::set_render_draw_color(0, 255, 0, 255);
			//Engine::draw_rectangle(Engine::rect2d(tileComponent->x_pos, tileComponent->y_pos, tileComponent->width, tileComponent->height));
			auto wallPos = manager->get_component<PositionComponent>(tile);
			auto collisionComponent = manager->get_component<CollisionComponent>(tile);

			const vector2d vec1 = vector2d(wallPos->x, wallPos->y);
			const vector2d vec2 = vector2d(wallPos->x + collisionComponent->width, wallPos->y);
			const vector2d vec3 = vector2d(wallPos->x + collisionComponent->width, wallPos->y + collisionComponent->height);
			const vector2d vec4 = vector2d(wallPos->x, wallPos->y + collisionComponent->height);

			if (intersects(enemyVec0, enemyVec1, vec1, vec2)) {
				int yDiff = wallPos->y - enemyVec0.y();
				vector2d collVector = oneY * yDiff;
				vector2d rest = collRange - collVector;
				if (length(collVector) < dist) {
					//tilePos = vector2d(wallPos->x + 32, wallPos->y);
					dist = length(collVector);
					if ((playerPos->x > enemyPos->x && enemyComponent->state == Pursuing) || (playerPos->x < enemyPos->x && enemyComponent->state == Fleeing)) {
						//left
						diff = normalize(vector2d(rest.y(), length(rest) * -1.5)) * length(rest);
					}
					else {
						diff = normalize(vector2d(rest.y() * -1, length(rest) * -1.5)) * length(rest);
					}
				}
			}
			if (intersects(enemyVec0, enemyVec1, vec2, vec3) && enemyVec0.x() != vec2.x()) {
				int xDiff = wallPos->x + collisionComponent->width - enemyVec0.x();
				vector2d collVector = oneX * xDiff;
				vector2d rest = collRange - collVector;

				if (length(collVector) < dist) {
					//tilePos = vector2d(wallPos->x + 64, wallPos->y + 32);
					dist = length(collVector);
					if ((playerPos->y > enemyPos->y && enemyComponent->state == Pursuing) || (playerPos->y < enemyPos->y && enemyComponent->state == Fleeing)) {
						//left
						diff = normalize(vector2d(length(rest) * 1.5, rest.x() * -1)) * length(rest);
					}
					else {
						diff = normalize(vector2d(length(rest) * 1.5, rest.x())) * length(rest);
					}
				}
			}
			if (intersects(enemyVec0, enemyVec1, vec4, vec3)) {
				int yDiff = wallPos->y + collisionComponent->height - enemyVec0.y();
				vector2d collVector = oneY * yDiff;
				vector2d rest = collRange - collVector;

				if (length(collVector) < dist) {
					//tilePos = vector2d(wallPos->x + 32, wallPos->y + 64);
					dist = length(collVector);
					if ((playerPos->x > enemyPos->x && enemyComponent->state == Pursuing) || (playerPos->x < enemyPos->x && enemyComponent->state == Fleeing)) {
						//left
						diff = normalize(vector2d(rest.y() * -1, length(rest) * 1.5)) * length(rest);
					}
					else {
						diff = normalize(vector2d(rest.y(), length(rest) * 1.5)) * length(rest);
					}
				}
			}
			if (intersects(enemyVec0, enemyVec1, vec1, vec4)) {
				int xDiff = wallPos->x - enemyVec0.x();
				vector2d collVector = oneX * xDiff;
				vector2d rest = collRange - collVector;
				if (length(collVector) < dist) {
					//tilePos = vector2d(wallPos->x, wallPos->y + 32);
					dist = length(collVector);
					if ((playerPos->y > enemyPos->y && enemyComponent->state == Pursuing) || (playerPos->y < enemyPos->y && enemyComponent->state == Fleeing)) {
						//left
						diff = normalize(vector2d(length(rest) * 1.5 * -1, rest.x())) * length(rest);
					}
					else {
						diff = normalize(vector2d(length(rest) * 1.5 * -1, rest.x() * -1)) * length(rest);
					}
				}
			}
		}

	}
	if (diff.x() != 0 || diff.y() != 0) {
		//Engine::render_line(pos->x, pos->y, pos->x + vel->steer_force.x() * 100, pos->y + vel->steer_force.y() * 100);
		//Engine::render_line(tilePos.x(), tilePos.y(), tilePos.x() + diff.x(), tilePos.y() + diff.y());
		return normalize((diff) * 0.1 + (vel->steer_force * 0.9)) * length(vel->steer_force);
	}
	return vel->steer_force;
}