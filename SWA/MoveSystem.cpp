#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

MoveSystem::MoveSystem(EntityManager* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	for (auto entity : manager->get_all_entities<VelocityComponent>())
	{
		auto position = manager->get_component<PositionComponent>(entity);
		auto velocity = manager->get_component<VelocityComponent>(entity);
		
	}
}
