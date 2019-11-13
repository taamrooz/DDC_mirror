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
#include "ladderComponent.h"
#include "RoomComponent.h"
#include "RoomSingleton.h"
#include "DamagingComponent.h"
ComponentFactory::ComponentFactory() {

}

ComponentFactory* ComponentFactory::instance_ = 0;

enum string_code {
	cPlayer,
	cWall,
	cChest,
	cladder,
	cMonster
};

string_code Convert(std::string const& inString) {
	if (inString == "player") return cPlayer;
	if (inString == "wall") return cWall;
	if (inString == "chest") return cChest;
	if (inString == "ladder") return cladder;
	if (inString == "monster") return cMonster;
	return cWall;
}

ComponentFactory* ComponentFactory::get_instance() {
	if (instance_ == 0)
	{
		instance_ = new ComponentFactory();
	}
	return instance_;
}

int ComponentFactory::CreateEntity(std::string name, int id, EntityManager* em) {
	switch (Convert(name)) {
	case cPlayer: {
		AddPlayerComponents(id, em);
		break;
	}
	case cChest: {
		AddChestComponents(id, em);
		break;
	}
	case cladder: {
		AddLadderComponents(id, em);
		break;
	}
	case cMonster: {
		AddEnemyComponents(id, em);
		break;
	}
	default: {
		//std::cout << "Error, entity name not found" << std::endl;
	}
	}
	return -1;
}

void ComponentFactory::AddChestComponents(int id, EntityManager* em) {
	auto coll = std::make_unique<CollisionComponent>(48, 48, PlayerCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	std::map<State, Animation> animations;
	animations.insert({ State::DEFAULT, Engine::LoadAnimation("Animations/chest_full_open.png", 3) });
	animations.at(State::DEFAULT).pause = true;
	animations.at(State::DEFAULT).scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto dmg = std::make_unique<DamagingComponent>(1, false);
	//ani.get()->animation.pause = true;
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(dmg));
  em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddPlayerComponents(int id, EntityManager* em) {
	auto hea = std::make_unique<HealthComponent>(5, 5);
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	std::map<State, Animation> animations;
	animations.insert({ State::DEFAULT, Engine::LoadAnimation("Animations/wizard_m_idle.png", 4) });
	animations.insert({ State::RUN, Engine::LoadAnimation("Animations/wizard_m_run.png", 4) });
	animations.insert({ State::HIT, Engine::LoadAnimation("Animations/wizard_m_hit.png", 1) });
	animations.at(State::DEFAULT).scale = 3;
	animations.at(State::RUN).scale = 3;
	animations.at(State::HIT).scale = 3;
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

void ComponentFactory::AddLadderComponents(int id, EntityManager* em) {
	auto ladder = std::make_unique<LadderComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 48, PlayerCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(ladder));
	em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddEnemyComponents(int id, EntityManager* em) {
	auto hea = std::make_unique<HealthComponent>(4, 5);
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	std::map<State, Animation> animations;
	animations.insert({ State::DEFAULT, Engine::LoadAnimation("Animations/wizard_m_idle.png", 4) });
	animations.insert({ State::RUN, Engine::LoadAnimation("Animations/wizard_m_run.png", 4) });
	animations.insert({ State::HIT, Engine::LoadAnimation("Animations/wizard_m_hit.png", 1) });
	animations.at(State::DEFAULT).scale = 3;
	animations.at(State::RUN).scale = 3;
	animations.at(State::HIT).scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto coll = std::make_unique<CollisionComponent>(48, 84, EnemyBulletCollisionHandler);
	em->add_component_to_entity(id, std::move(hea));
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
}