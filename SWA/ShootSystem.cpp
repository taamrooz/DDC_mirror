#include "ShootSystem.h"
#include "UserInput.h"
#include "ControllableComponent.h"

ShootSystem::ShootSystem(EntityManager* manager, InputComponent* inputcomponent) : BaseSystem(manager) {
	input_component = inputcomponent;
}

void ShootSystem::update(double dt)
{
	auto entity = manager_->get_all_entities<ControllableComponent>().front();
	auto position = manager_->get_component<PositionComponent>(entity);

	for (auto i = input_component->keys_down.begin(); i != input_component->keys_down.end(); ++i)
	{
		if (i->second) {
			if (!i->first.compare("shootUp")) {
				createBullet(position.x, position.y, 0, -30);
			}
			if (!i->first.compare("shootLeft")) {
				createBullet(position.x, position.y, -30, 0);
			}

			if (!i->first.compare("shootDown")) {
				createBullet(position.x, position.y, 0, 30);
			}

			if (!i->first.compare("shootRight")) {
				createBullet(position.x, position.y, 30, 0);
			}
			i->second = false;
		}
	}
}

void ShootSystem::createBullet(int x, int y, int xV, int yV) {
	const auto id = manager_->create_entity();
	auto vComponent = std::make_shared<VelocityComponent>(xV, yV);
	auto pComponent = std::make_shared<PositionComponent>(x, y);
	auto aComponent = std::make_shared<AnimationComponent>("Animations/tiny_zombie_run.png", 4);
	manager_->add_component_to_entity(id, vComponent);
	manager_->add_component_to_entity(id, pComponent);
	manager_->add_component_to_entity(id, aComponent);

}