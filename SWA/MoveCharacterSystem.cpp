#include "MoveCharacterSystem.h"
#include "EntityManager.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "KeyBindingSingleton.h"
#include "AnimationComponent.h"
#include "Renderer.h"

MoveCharacterSystem::MoveCharacterSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {
}

void MoveCharacterSystem::update(double dt) {

	//Get all relevant components for the player character
	auto entities = manager_->get_all_entities_from_current_room<CharacterComponent>();
	if (entities.empty()) return;
	auto entity = entities.front();
	auto velocity = manager_->get_component<VelocityComponent>(entity);
	auto position = manager_->get_component<PositionComponent>(entity);
	auto animation = manager_->get_component<AnimationComponent>(entity);

	int counter = 0;

	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.second) {
			if (i.first == KeyBindingSingleton::get_instance()->get_move_up_key()) {
				counter++;
			}

			if (i.first == KeyBindingSingleton::get_instance()->get_move_left_key()) {
				counter++;
			}

			if (i.first == KeyBindingSingleton::get_instance()->get_move_down_key()) {
				counter++;
			}

			if (i.first == KeyBindingSingleton::get_instance()->get_move_right_key()) {
				counter++;
			}
		}
	}

	//Go through possible actions and check if any need to be executed
	for (auto& i : KeyBindingSingleton::get_instance()->keys_down)
	{
		if (i.second)
		{
			if (i.first == KeyBindingSingleton::get_instance()->get_move_up_key()) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dy = (counter > 1) ? velocity->dy = -1 * diagonal_move_velocity : velocity->dy = -1 * move_velocity;
			}

			if (i.first == KeyBindingSingleton::get_instance()->get_move_left_key()) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dx = (counter > 1) ? velocity->dx = -1 * diagonal_move_velocity : velocity->dx = -1 * move_velocity;
				animation->flip_horizontally = true;
			}

			if (i.first == KeyBindingSingleton::get_instance()->get_move_down_key()) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dy = (counter > 1) ? velocity->dy = diagonal_move_velocity : velocity->dy = move_velocity;
			}

			if (i.first == KeyBindingSingleton::get_instance()->get_move_right_key()) {
				if (animation->lock_until < Engine::get_ticks()) {
					animation->currentState = State::RUN;
				}
				velocity->dx = (counter > 1) ? velocity->dx = diagonal_move_velocity : velocity->dx = move_velocity;
				animation->flip_horizontally = false;
			}
		}

	}
}