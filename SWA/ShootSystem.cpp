#include "ShootSystem.h"
#include "UserInput.h"
#include "ShootingComponent.h"
#include "KeyBindingSingleton.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include "PositionComponent.h"
#include "RoomSingleton.h"
#include "RoomComponent.h"
#include "DamagingComponent.h"
#include "Renderer.h"
#include "VelocityComponent.h"
#include "CollisionHandlers.h"
#include "Audio.h"
#include "AnimationComponent.h"

ShootSystem::ShootSystem(Engine::EntityManager<Component>* manager) : BaseSystem(manager) {
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
				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_up_key()) {
					int xPos = position->x + collision->width / 2;
					int yPos = (position->y - sComponent->bullet_size + 20) - 1;
					createBullet(0, -1 * bullet_velocity, xPos, yPos, dt);
				}
				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_left_key()) {
					int xPos = position->x - sComponent->bullet_size;
					int yPos = position->y + (collision->height / 2) + 15;
					createBullet(-1 * bullet_velocity, 0, xPos, yPos, dt);
				}

				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_down_key()) {
					int xPos = position->x + collision->width / 2;
					int yPos = position->y + collision->height + 1 + 20;
					createBullet(0, bullet_velocity, xPos, yPos, dt);
				}

				if (i->first == KeyBindingSingleton::get_instance()->get_shoot_right_key()) {
					int xPos = position->x + collision->width + 1;
					int yPos = position->y + collision->height / 2 + 15;
					createBullet(bullet_velocity, 0, xPos, yPos, dt);
				}

			}
		}
	}
}

void ShootSystem::createBullet(int xV, int yV, int x, int y, double dt) {
	auto entity = manager_->get_all_entities_from_current_room<CharacterComponent>().front();
	auto shoot = manager_->get_component<ShootingComponent>(entity);
	auto dmg = std::make_unique<DamagingComponent>(1, false);
	auto room = std::make_unique<RoomComponent>(DungeonSingleton::get_instance()->get_current_room()->room_name, DungeonSingleton::get_instance()->get_current_room_number());

	Uint32 ticks = Engine::get_ticks();
	if (ticks - shoot->last_shot >= shoot->fire_rate / dt) {
		Engine::play_audio("shoot.wav");
		auto position = manager_->get_component<PositionComponent>(entity);
		auto collision = manager_->get_component<CollisionComponent>(entity);

		const auto id = manager_->create_entity();

		auto vComponent = std::make_unique<VelocityComponent>(xV, yV);
		auto pComponent = std::make_unique<PositionComponent>(x, y);
		std::unordered_map<State, std::unique_ptr<Animation>> animations;
		std::unordered_map<State, std::string> state_to_path;
		std::unordered_map<State, int> state_to_frames;
		animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::unique_ptr<Animation>(Engine::load_animation("Projectile1.png", 1))));
		state_to_path.emplace(State::DEFAULT, "Projectile1.png");
		state_to_frames.emplace(State::DEFAULT, 1);
		animations.at(State::DEFAULT)->scale = 2;
		auto aComponent = std::make_unique<AnimationComponent>(animations, state_to_path, state_to_frames);
		auto cComponent = std::make_unique<CollisionComponent>(shoot->bullet_size * 2, shoot->bullet_size * 2, PlayerBulletCollisionHandler, CollisionHandlerNames::PlayerBulletCollisionHandler, false, entity);
		manager_->add_component_to_entity(id, std::move(vComponent));
		manager_->add_component_to_entity(id, std::move(pComponent));
		manager_->add_component_to_entity(id, std::move(aComponent));
		manager_->add_component_to_entity(id, std::move(cComponent));
		manager_->add_component_to_entity(id, std::move(dmg));
		manager_->add_component_to_entity(id, std::move(room));
		shoot->last_shot = Engine::get_ticks();
	}
	

}