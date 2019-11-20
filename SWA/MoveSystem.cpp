#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"

MoveSystem::MoveSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	//Get player character
	auto entities = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (!entities.empty()) {
		auto characterEntity = entities.front();

		//Resolve velocity
		for (auto entity : manager_->get_all_entities_from_current_room<VelocityComponent>())
		{
			auto position = manager_->get_component<PositionComponent>(entity);

		auto velocity = manager_->get_component<VelocityComponent>(entity);
		position->x = position->x + velocity->dx;
		position->y = position->y + velocity->dy;
		if(velocity->dropOff != 0) {
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
