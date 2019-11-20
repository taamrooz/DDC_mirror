#include "ComponentFactory.h"
#include <iostream>
#include "PositionComponent.h"
#include "ShootingComponent.h"
#include "VelocityComponent.h"
#include "AnimationComponent.h"
#include "CharacterComponent.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"
#include "CollisionHandlers.h"
#include "LadderComponent.h"
#include "RoomComponent.h"
#include "RoomSingleton.h"
#include "DamagingComponent.h"
#include "Renderer.h"

ComponentFactory::ComponentFactory() {

}

ComponentFactory* ComponentFactory::instance_ = 0;

enum class string_code {
	cPlayer,
	cWall,
	cChest,
	cladder,
	cMonster
};

string_code Convert(std::string const& inString) {
	if (inString == "player") return string_code::cPlayer;
	if (inString == "wall") return string_code::cWall;
	if (inString == "chest") return string_code::cChest;
	if (inString == "ladder") return string_code::cladder;
	if (inString == "monster") return string_code::cMonster;
	return string_code::cWall;
}

ComponentFactory* ComponentFactory::get_instance() {
	if (instance_ == 0)
	{
		instance_ = new ComponentFactory();
	}
	return instance_;
}

int ComponentFactory::CreateEntity(std::string name, int id, Engine::EntityManager<Component>* em) {
	switch (Convert(name)) {
	case string_code::cPlayer: {
		AddPlayerComponents(id, em);
		break;
	}
	case string_code::cChest: {
		AddChestComponents(id, em);
		break;
	}
	case string_code::cladder: {
		AddLadderComponents(id, em);
		break;
	}
	case string_code::cMonster: {
		AddEnemyComponents(id, em);
		break;
	}
	default: {
		//std::cout << "Error, entity name not found" << std::endl;
	}
	}
	return -1;
}

void ComponentFactory::AddChestComponents(int id, Engine::EntityManager<Component>* em) {
	auto coll = std::make_unique<CollisionComponent>(48, 48, PlayerCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::make_unique<Animation>(*Engine::load_animation("Animations/chest_full_open.png", 3) )));
	animations.at(State::DEFAULT)->pause = true;
	animations.at(State::DEFAULT)->scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto dmg = std::make_unique<DamagingComponent>(1, false);
	//ani.get()->animation.pause = true;
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(dmg));
  em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddPlayerComponents(int id, Engine::EntityManager<Component>* em) {
	auto hea = std::make_unique<HealthComponent>(5, 5);
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::make_unique<Animation>(*Engine::load_animation("Animations/wizard_m_idle.png", 4)) ));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::RUN, std::make_unique<Animation>(*Engine::load_animation("Animations/wizard_m_run.png", 4) )));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::HIT, std::make_unique<Animation>(*Engine::load_animation("Animations/wizard_m_hit.png", 1) )));
	animations.at(State::DEFAULT)->scale = 3;
	animations.at(State::RUN)->scale = 3;
	animations.at(State::HIT)->scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto cha = std::make_unique<CharacterComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 84, PlayerCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	em->add_component_to_entity(id, std::move(hea));
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(cha));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
	em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddLadderComponents(int id, Engine::EntityManager<Component>* em) {
	auto ladder = std::make_unique<LadderComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 48, PlayerCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(ladder));
	em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddEnemyComponents(int id, Engine::EntityManager<Component>* em) {
	auto hea = std::make_unique<HealthComponent>(4, 5);
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::make_unique<Animation>(*Engine::load_animation("Animations/wizard_m_idle.png", 4)) ));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::RUN, std::make_unique<Animation>(*Engine::load_animation("Animations/wizard_m_run.png", 4) )));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::HIT, std::make_unique<Animation>(*Engine::load_animation("Animations/wizard_m_hit.png", 1) )));
	animations.at(State::DEFAULT)->scale = 3;
	animations.at(State::RUN)->scale = 3;
	animations.at(State::HIT)->scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto coll = std::make_unique<CollisionComponent>(48, 84, EnemyBulletCollisionHandler);
	em->add_component_to_entity(id, std::move(hea));
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
}