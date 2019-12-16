#include "MoveSystem.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CharacterComponent.h"
#include "EnemyComponent.h"
#include <vector2d.h>
#include "SteeringBehaviors.h"


MoveSystem::MoveSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {}

void MoveSystem::update(double dt)
{
	

	//Get player character
	auto player = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (!player.empty()) {
		auto characterEntity = player.front();

		//Resolve velocity
		for (auto entity : manager_->get_all_entities_from_current_room<VelocityComponent>())
		{
		auto playerPosition = manager_->get_component<PositionComponent>(entity);

			auto velocity = manager_->get_component<VelocityComponent>(entity);
			playerPosition->x = playerPosition->x + velocity->dx * dt;
			playerPosition->y = playerPosition->y + velocity->dy * dt;
			if (velocity->dropOff != 0) {
				if (velocity->dx < 0) {
					velocity->dx = velocity->dx + velocity->dropOff > 0 ? 0 : velocity->dx + velocity->dropOff;
				}
				else if (velocity->dx > 0) {
					velocity->dx = velocity->dx - velocity->dropOff < 0 ? 0 : velocity->dx - velocity->dropOff;
				}
				else if (velocity->dy < 0) {
					velocity->dy = velocity->dy + velocity->dropOff > 0 ? 0 : velocity->dy + velocity->dropOff;
				}
				else if (velocity->dy > 0) {
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
