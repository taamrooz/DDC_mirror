#include "ShootSystem.h"
#include "UserInput.h"
#include "ShootingComponent.h"
#include "KeyBindingSingleton.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"

ShootSystem::ShootSystem(EntityManager* manager, InputComponent* inputcomponent) : BaseSystem(manager) {
	input_component = inputcomponent;
}

void ShootSystem::update(double dt)
{
	for (auto i = KeyBindingSingleton::get_instance()->keys_down.begin(); i != KeyBindingSingleton::get_instance()->keys_down.end(); ++i)
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
	auto entity = manager_->get_all_entities<CharacterComponent>().front();
	auto shoot = &manager_->get_component<ShootingComponent>(entity);
	Uint32 ticks = Engine::GetTicks();

	if (ticks - shoot->last_shot >= shoot->fire_rate) {
		auto position = manager_->get_component<PositionComponent>(entity);
		auto collision = manager_->get_component<CollisionComponent>(entity);

		const auto id = manager_->create_entity();

		auto vComponent = std::make_shared<VelocityComponent>(xV, yV);
		auto pComponent = std::make_shared<PositionComponent>(position.x + collision.width / 2, position.y + collision.height / 2);
		auto aComponent = std::make_shared<AnimationComponent>("Projectile.png", 1);

		manager_->add_component_to_entity(id, vComponent);
		manager_->add_component_to_entity(id, pComponent);
		manager_->add_component_to_entity(id, aComponent);
		shoot->last_shot = Engine::GetTicks();
	}
	

}