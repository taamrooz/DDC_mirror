#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

MoveSystem::MoveSystem(EntityManager* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	for (auto entity : manager_->get_all_entities<VelocityComponent>())
	{
		auto position = manager_->get_component<PositionComponent>(entity);
		std::cout << "x: " << position->x << " y: " << position->y << std::endl;
		auto velocity = manager_->get_component<VelocityComponent>(entity);
		std::cout << "dx: " << velocity->dx << " dy: " << velocity->dy << std::endl;
		position->x += velocity->dx * dt;
		position->y += velocity->dy * dt;
		
	}
}
