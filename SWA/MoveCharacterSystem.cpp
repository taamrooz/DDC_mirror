#include "MoveCharacterSystem.h"
#include "CharacterComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
MoveCharacterSystem::MoveCharacterSystem(EntityManager* manager, InputComponent* inputcomponent) : BaseSystem(manager) {
	input_component = inputcomponent;
}

void MoveCharacterSystem::update(double dt) {
	auto entity = manager_->get_all_entities<CharacterComponent>().front();
	auto position = manager_->get_component<PositionComponent>(entity);
	std::cout << position.x << std::endl;
	auto velocity = manager_->get_component<VelocityComponent>(entity);
		
	for (auto i = input_component->keys_down.begin(); i != input_component->keys_down.end(); ++i)
	{
		if (i->second) {
			if (i->first.compare("moveUP"))
				position.y -= velocity.dy;
			if (i->first.compare("moveLeft"))
				position.x -= velocity.dx;
			if (i->first.compare("moveDown"))
				position.y += velocity.dy;
			if (i->first.compare("moveRight"))
				position.x += velocity.dx;
		}
	}
	position.x = position.x + velocity.dx;
	position.y = position.y + velocity.dy;
}