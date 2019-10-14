#include "MoveCharacterSystem.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
MoveCharacterSystem::MoveCharacterSystem(EntityManager* manager, InputComponent* inputcomponent) : BaseSystem(manager) {
	input_component = inputcomponent;
}

void MoveCharacterSystem::update(double dt) {
	auto entity = manager_->get_all_entities<CharacterComponent>().front();
	auto velocity = manager_->get_component<VelocityComponent>(entity);
		
	for (auto i = input_component->keys_down.begin(); i != input_component->keys_down.end(); ++i)
	{
		if (i->first.compare("moveUP")) {
			if (i->second) {
				velocity.dy = -2;
			}
			else {
				velocity.dy = 0;
			}
		}
			
		if (i->first.compare("moveLeft")) {
			if (i->second) {
				velocity.dx = -2;
			}
			else {
				velocity.dx = 0;
			}
		}

		if (i->first.compare("moveDown")) {
			if (i->second) {
				velocity.dy = 2;
			}
			else {
				velocity.dy = 0;
			}
		}

		if (i->first.compare("moveRight")) {
			if (i->second) {
				velocity.dx = 2;
			}
			else {
				velocity.dx = 0;
			}
		}
	}
}