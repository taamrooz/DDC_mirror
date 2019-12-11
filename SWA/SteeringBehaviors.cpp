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

	//auto pos = manager->get_component<PositionComponent>(entity);

	////the feelers are contained in a 
	//std::vector<vector2d> m_Feelers = CreateFeelers(entity, manager);
	//double DistToThisIP = 0.0;
	//double DistToClosestIP = 100000.0;
	////this will hold an index into the vector of walls 
	//int ClosestWall = -1;
	//std::vector<int> walls;

	//auto tiles = manager->get_all_entities_from_current_room<TileComponent>();
	//for (int tile : tiles) {
	//	auto coll = manager->get_component<CollisionComponent>(tile);
	//	if (coll != nullptr) {
	//		walls.push_back(tile);
	//	}
	//}

	//vector2d SteeringForce,
	//	point, //used for storing temporary info 
	//	ClosestPoint; //holds the closest intersection point
	////examine each feeler in turn 
	//	for (int flr = 0; flr < m_Feelers.size(); ++flr)
	//	{ 
	//		//run through each wall checking for any intersection points 
	//		for (int w = 0; w < walls.size(); ++w) {
	//			auto wall = manager->get_component<PositionComponent>(walls[w]);
	//			if(normalize(vector2d(wall->x, wall->y)) == normalize()
	//			if (LineIntersection(manager, m_Feelers[flr], walls[w], DistToThisIP, point))
	//			{ 

	//				//is this the closest found so far? If so keep a record 
	//				if (DistToThisIP < DistToClosestIP) {
	//					DistToClosestIP = DistToThisIP;
	//					ClosestWall = w;
	//					ClosestPoint = point;
	//				}
	//			}
	//		}//next wall
	//	//if an intersection point has been detected, calculate a force 
	//	//that will direct the agent away 
	//		if (ClosestWall >=0) { 
	//			//calculate by what distance the projected position of the agent 
	//			//will overshoot the wall Vector2D 
	//			OverShoot = m_Feelers[flr] - ClosestPoint;
	//			//create a force in the direction of the wall normal, with a magnitude of the overshoot 
	//			SteeringForce = walls[ClosestWall].Normal() * OverShoot.Length();
	//		}
	//	}//next feeler
	//return SteeringForce;
	return vector2d();
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