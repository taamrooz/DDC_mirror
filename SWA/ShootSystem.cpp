#include "ShootSystem.h"
#include "UserInput.h"
#include "ControllableComponent.h"
#include "ShootingComponent.h"

ShootSystem::ShootSystem(EntityManager* manager, InputComponent* inputcomponent) : BaseSystem(manager) {
	input_component = inputcomponent;
}

void ShootSystem::update(double dt)
{
	

	for (auto i = input_component->keys_down.begin(); i != input_component->keys_down.end(); ++i)
	{
		if (i->second) {
			if (!i->first.compare("shootUp")) {
				createBullet(0, -1 * bullet_velocity);
				i->second = false;
			}
			if (!i->first.compare("shootLeft")) {
				createBullet(-1 * bullet_velocity, 0);
				i->second = false;
			}

			if (!i->first.compare("shootDown")) {
				createBullet(0, bullet_velocity);
				i->second = false;
			}

			if (!i->first.compare("shootRight")) {
				createBullet(bullet_velocity, 0);
				i->second = false;
			}
			
		}
	}
}

void ShootSystem::createBullet(int xV, int yV) {
	auto entity = manager_->get_all_entities<ControllableComponent>().front();
	auto position = manager_->get_component<PositionComponent>(entity);

	const auto id = manager_->create_entity();
	auto vComponent = std::make_shared<VelocityComponent>(xV, yV);
	auto pComponent = std::make_shared<PositionComponent>(position.x + 50, position.y + 100);
	auto aComponent = std::make_shared<AnimationComponent>("Projectile.png", 1);
	auto bComponent = std::make_shared<ShootingComponent>(4);

	manager_->add_component_to_entity(id, vComponent);
	manager_->add_component_to_entity(id, pComponent);
	manager_->add_component_to_entity(id, aComponent);
	manager_->add_component_to_entity(id, bComponent);

}