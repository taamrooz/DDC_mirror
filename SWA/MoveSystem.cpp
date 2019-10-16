#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"

MoveSystem::MoveSystem(EntityManager* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	//Get player character
	auto characterEntity = manager_->get_all_entities<CharacterComponent>().front();

	//Resolve velocity
	for (auto entity : manager_->get_all_entities<VelocityComponent>())
	{
		auto position = manager_->get_component<PositionComponent>(entity);

		auto velocity = manager_->get_component<VelocityComponent>(entity);
		position->x = position->x + velocity->dx;
		position->y = position->y + velocity->dy;

		if (characterEntity == entity) {
			velocity->dx = 0;
			velocity->dy = 0;
		}
	}
}
