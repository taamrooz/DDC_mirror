#include "MoveCharacterSystem.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "KeyBindingSingleton.h"
#include "AnimationComponent.h"

MoveCharacterSystem::MoveCharacterSystem(EntityManager* manager) : BaseSystem(manager) {
}

void MoveCharacterSystem::update(double dt) {
	auto entity = manager_->get_all_entities<CharacterComponent>().front();
	auto velocity = &manager_->get_component<VelocityComponent>(entity);
	auto position = &manager_->get_component<PositionComponent>(entity);
	auto animation = manager_->get_component<AnimationComponent>(entity);

	for (auto i = KeyBindingSingleton::get_instance()->keys_down.begin(); i != KeyBindingSingleton::get_instance()->keys_down.end(); ++i)
	{
		if (i->first.compare("moveUP") == 0) {
			if (i->second) {
				velocity->dy = -1 * move_velocity;
			}
		}

		if (i->first.compare("moveLeft") == 0) {
			if (i->second) {
				velocity->dx = -1 * move_velocity;
			}
		}

		if (i->first.compare("moveDown") == 0) {
			if (i->second) {
				velocity->dy = move_velocity;
			}
		}

		if (i->first.compare("moveRight") == 0) {
			if (i->second) {
				velocity->dx = move_velocity;
			}
		}
	}
}