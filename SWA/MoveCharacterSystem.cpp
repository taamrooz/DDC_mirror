#include "MoveCharacterSystem.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "KeyBindingSingleton.h"
#include "AnimationComponent.h"

MoveCharacterSystem::MoveCharacterSystem(EntityManager* manager) : BaseSystem(manager) {
}

void MoveCharacterSystem::update(double dt) {

	//Get all relevant components for the player character
	auto entity = manager_->get_all_entities<CharacterComponent>().front();
	auto velocity = manager_->get_component<VelocityComponent>(entity);
	auto position = manager_->get_component<PositionComponent>(entity);
	auto animation = manager_->get_component<AnimationComponent>(entity);

	//Go through possible actions and check if any need to be executed
	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.first == "moveUP") {
			if (i.second) {
				velocity->dy = -1 * move_velocity;
			}
		}

		if (i.first == "moveLeft") {
			if (i.second) {
				velocity->dx = -1 * move_velocity;
				animation->flip_horizontally = true;
			}
		}

		if (i.first == "moveDown") {
			if (i.second) {
				velocity->dy = move_velocity;
			}
		}

		if (i.first == "moveRight") {
			if (i.second) {
				velocity->dx = move_velocity;
			}
		}
	}
}