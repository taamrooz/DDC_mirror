#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"

MoveSystem::MoveSystem(EntityManager* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	auto characterEntity = manager_->get_all_entities<CharacterComponent>().front();

	for (auto entity : manager_->get_all_entities<VelocityComponent>())
	{
		auto position = &manager_->get_component<PositionComponent>(entity);
		std::cout << position->x << std::endl;
		auto velocity = &manager_->get_component<VelocityComponent>(entity);

		if (characterEntity == entity) {
			int x = 0;
		}
		position->x = position->x + velocity->dx;
		position->y = position->y + velocity->dy;
	}
}
