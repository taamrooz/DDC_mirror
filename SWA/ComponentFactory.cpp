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
#include "ChestComponent.h"
#include "InventoryComponent.h"
#include "LevelBossComponent.h"
#include "LevelSingleton.h"
#include "Renderer.h"
#include "EnemyComponent.h"

ComponentFactory::ComponentFactory() {

}

ComponentFactory* ComponentFactory::instance_ = 0;

string_code Convert(std::string const& inString) {
	if (inString == "player") return cPlayer;
	if (inString == "wall") return cWall;
	if (inString == "chest") return cChest;
	if (inString == "ladder") return cladder;
	if (inString == "Flask_Blue") return cFlask_Blue;
	if (inString == "monster") return cMonster;
	if (inString == "boss") return cBoss;
	return cWall;
}

ComponentFactory* ComponentFactory::get_instance() {
	if (instance_ == 0)
	{
		instance_ = new ComponentFactory();
	}
	return instance_;
}

int ComponentFactory::CreateEntity(std::string const& name, int id, Engine::EntityManager<Component>* em) {
	return CreateEntity(Convert(name), id, em);
}

int ComponentFactory::CreateEntity(string_code name, int id, Engine::EntityManager<Component>* em)
{
	switch (name) {
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
	case cFlask_Blue: {
		AddBlueFlaskComponents(id, em);
		break;
	}
	case cMonster: {
		AddEnemyComponents(id, em, false);
		break;
	}
	case cBoss: {
		AddEnemyComponents(id, em, true);
		break;
	}
	default: {
		//std::cout << "Error, entity name not found" << std::endl;
	}
	}
	return -1;
}

void ComponentFactory::AddChestComponents(int id, Engine::EntityManager<Component>* em) {
	auto coll = std::make_unique<CollisionComponent>(48, 48, ChestCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->get_current_room_name());
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::make_unique<Animation>(*Engine::load_animation("Animations/chest_full_open.png", 3))));
	animations.at(State::DEFAULT)->pause = true;
	animations.at(State::DEFAULT)->scale = 3;
	animations.at(State::DEFAULT)->loop = false;
	auto ani = std::make_unique<AnimationComponent>(animations);
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
    em->add_component_to_entity(id, std::move(room));

	//create chestComponent and add to the entity
	auto chest = std::make_unique<ChestComponent>(string_code::cFlask_Blue);
	em->add_component_to_entity(id, std::move(chest));
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
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->get_current_room_name());
	auto inv = std::make_unique<InventoryComponent>();
	em->add_component_to_entity(id, std::move(hea));
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(cha));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
	em->add_component_to_entity(id, std::move(room));
	em->add_component_to_entity(id, std::move(inv));
}

void ComponentFactory::AddLadderComponents(int id, Engine::EntityManager<Component>* em) {
	auto ladder = std::make_unique<LadderComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 48, PlayerCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->get_current_room_name());
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(ladder));
	em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddEnemyComponents(int id, Engine::EntityManager<Component>* em, bool level_boss) {
	auto hea = std::make_unique<HealthComponent>(4, 5);
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	auto emc = std::make_unique<EnemyComponent>();
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->get_current_room_name());
	auto damage = std::make_unique<DamagingComponent>(1);
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::make_unique<Animation>(*Engine::load_animation("Animations/orc_shaman_idle.png", 4)) ));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::RUN, std::make_unique<Animation>(*Engine::load_animation("Animations/orc_shaman_run.png", 4) )));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::HIT, std::make_unique<Animation>(*Engine::load_animation("Animations/orc_shaman_idle.png", 4) )));
	animations.at(State::DEFAULT)->scale = 3;
	animations.at(State::RUN)->scale = 3;
	animations.at(State::HIT)->scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto coll = std::make_unique<CollisionComponent>(48, 84, EnemyCollisionHandler, false);
	em->add_component_to_entity(id, std::move(damage));
	em->add_component_to_entity(id, std::move(emc));
	em->add_component_to_entity(id, std::move(hea));
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
	
	if (level_boss) {
		auto boss = std::make_unique<LevelBossComponent>();
		em->add_component_to_entity(id, std::move(boss));
	}
}

void ComponentFactory::AddBlueFlaskComponents(int id, Engine::EntityManager<Component>* em) {

	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::make_unique<Animation>(*Engine::load_animation("flask_big_blue.png", 1))));
	animations.at(State::DEFAULT)->scale = 2;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->get_current_room_name());
	auto coll = std::make_unique<CollisionComponent>(32, 32, ItemCollisionHandler, false);
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(room));

}