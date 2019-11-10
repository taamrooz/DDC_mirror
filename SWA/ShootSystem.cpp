#include "ShootSystem.h"
#include "UserInput.h"
#include "ShootingComponent.h"
#include "KeyBindingSingleton.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"

ShootSystem::ShootSystem(EntityManager* manager) : BaseSystem(manager) {
}

void ShootSystem::update(double dt)
{
	for (auto i = KeyBindingSingleton::get_instance()->keys_down.begin(); i != KeyBindingSingleton::get_instance()->keys_down.end(); ++i)
	{
		if (i->second) {
			auto entities = manager_->get_all_entities_from_current_room<CharacterComponent>();
			if (!entities.empty()) {
				auto entity = entities.front();
				auto sComponent = manager_->get_component<ShootingComponent>(entity);
				auto collision = manager_->get_component<CollisionComponent>(entity);
				auto position = manager_->get_component<PositionComponent>(entity);
				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_up_key_binding()) {
					int xPos = position->x + collision->width / 2;
					int yPos = (position->y - sComponent->bullet_size + 20) - 1;
					createBullet(0, -1 * bullet_velocity, xPos, yPos);
					i->second = false;
				}
				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_left_key_binding()) {
					int xPos = position->x - sComponent->bullet_size;
					int yPos = position->y + (collision->height / 2) + 15;
					createBullet(-1 * bullet_velocity, 0, xPos, yPos);
					i->second = false;
				}

				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_down_key_binding()) {
					int xPos = position->x + collision->width / 2;
					int yPos = position->y + collision->height + 1 + 20;
					createBullet(0, bullet_velocity, xPos, yPos);
					i->second = false;
				}

				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_right_key_binding()) {
					int xPos = position->x + collision->width + 1;
					int yPos = position->y + collision->height / 2 + 15;
					createBullet(bullet_velocity, 0, xPos, yPos);
					i->second = false;
				}

			}
		}
	}
}

void ShootSystem::createBullet(int xV, int yV, int x, int y) {
	auto entity = manager_->get_all_entities_from_current_room<CharacterComponent>().front();
	auto shoot = manager_->get_component<ShootingComponent>(entity);
	Uint32 ticks = Engine::GetTicks();
	if (ticks - shoot->last_shot >= shoot->fire_rate) {
		auto position = manager_->get_component<PositionComponent>(entity);
		auto collision = manager_->get_component<CollisionComponent>(entity);

		const auto id = manager_->create_entity();

		auto vComponent = std::make_unique<VelocityComponent>(xV, yV);
		auto pComponent = std::make_unique<PositionComponent>(x, y);
		auto aComponent = std::make_unique<AnimationComponent>("Projectile.png", 1, 2);
		auto cComponent = std::make_unique<CollisionComponent>(shoot->bullet_size * 2, shoot->bullet_size * 2, BulletCollisionHandler, entity);
		manager_->add_component_to_entity(id, std::move(vComponent));
		manager_->add_component_to_entity(id, std::move(pComponent));
		manager_->add_component_to_entity(id, std::move(aComponent));
		manager_->add_component_to_entity(id, std::move(cComponent));
		shoot->last_shot = Engine::GetTicks();
	}
	

}