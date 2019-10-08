#include "CollisionSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

CollisionSystem::CollisionSystem(EntityManager* manager) : BaseSystem(manager) {}

void CollisionSystem::update(double dt)
{
	for (auto entity : manager_->get_all_entities<VelocityComponent>())
	{
		auto position = manager_->get_component<PositionComponent>(entity);
		std::cout << position.x << std::endl;
		auto velocity = manager_->get_component<VelocityComponent>(entity);
		
	}
}
