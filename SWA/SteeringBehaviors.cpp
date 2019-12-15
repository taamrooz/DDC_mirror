#include "SteeringBehaviors.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "TileComponent.h"
#include "CollisionComponent.h"

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
	if (evaderPos->x == pos->x && evaderPos->y == pos->y) {
		return vector2d(evaderVelocity->dx * -1, evaderVelocity->dy * -1);
	}
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