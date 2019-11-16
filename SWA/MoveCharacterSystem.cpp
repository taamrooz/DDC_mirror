#include "MoveCharacterSystem.h"
#include "EntityManager.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "KeyBindingSingleton.h"
#include "AnimationComponent.h"

MoveCharacterSystem::MoveCharacterSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {
}

void MoveCharacterSystem::update(double dt) {

	//Get all relevant components for the player character
	auto entity = manager_->get_all_entities_from_current_room<CharacterComponent>().front();
	auto velocity = manager_->get_component<VelocityComponent>(entity);
	auto position = manager_->get_component<PositionComponent>(entity);
	auto animation = manager_->get_component<AnimationComponent>(entity);

	int counter = 0;

	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.first == KeyBindingSingleton::get_instance()->get_move_up_key_binding()) {
			if (i.second) {
				counter++;
			}
		}

		if (i.first == KeyBindingSingleton::get_instance()->get_move_left_key_binding()) {
			if (i.second) {
				counter++;
			}
		}

		if (i.first == KeyBindingSingleton::get_instance()->get_move_down_key_binding()) {
			if (i.second) {
				counter++;
			}
		}

		if (i.first == KeyBindingSingleton::get_instance()->get_move_right_key_binding()) {
			if (i.second) {
				counter++;
			}
		}
	}

	//Go through possible actions and check if any need to be executed
	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.first == KeyBindingSingleton::get_instance()->get_move_up_key_binding()) {
			if (i.second) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dy = (counter > 1) ? velocity->dy = -1 * diagonal_move_velocity : velocity->dy = -1 * move_velocity;
			}
		}

		if (i.first == KeyBindingSingleton::get_instance()->get_move_left_key_binding()) {
			if (i.second) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dx = (counter > 1) ? velocity->dx = -1 * diagonal_move_velocity : velocity->dx = -1 * move_velocity;
				animation->flip_horizontally = true;
			}
		}

		if (i.first == KeyBindingSingleton::get_instance()->get_move_down_key_binding()) {
			if (i.second) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dy = (counter > 1) ? velocity->dy = diagonal_move_velocity : velocity->dy = move_velocity;
			}
		}

		if (i.first == KeyBindingSingleton::get_instance()->get_move_right_key_binding()) {
			if (i.second) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dx = (counter > 1) ? velocity->dx = diagonal_move_velocity : velocity->dx = move_velocity;
				animation->flip_horizontally = false;
			}
		}
	}
}