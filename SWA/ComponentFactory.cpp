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
#include "DamagingComponent.h"
#include "ChestComponent.h"
ComponentFactory::ComponentFactory() {

}

ComponentFactory* ComponentFactory::instance_ = 0;



string_code Convert(std::string const& inString) {
	if (inString == "player") return cPlayer;
	if (inString == "wall") return cWall;
	if (inString == "chest") return cChest;
	if (inString == "Flask_Blue") return cFlask_Blue;
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
	return CreateEntity(Convert(name), id, em);
}

int ComponentFactory::CreateEntity(string_code name, int id, EntityManager* em)
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
	case cFlask_Blue: {
		AddBlueFlaskComponents(id, em);
	}
	default: {
		//std::cout << "Error, entity name not found" << std::endl;
	}
	}
	return -1;
}

//int ComponentFactory::CreateEntity(string_code name, int id, EntityManager* em) {

//}

void ComponentFactory::AddChestComponents(int id, EntityManager* em) {
	//create chest
	auto coll = std::make_unique<CollisionComponent>(48, 48, ChestCollisionHandler);
	std::map<State, Animation> animations;
	animations.insert({ State::DEFAULT, Engine::LoadAnimation("Animations/chest_full_open.png", 3) });
	animations.at(State::DEFAULT).pause = true;
	animations.at(State::DEFAULT).loop = false;
	animations.at(State::DEFAULT).scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations);
	auto dmg = std::make_unique<DamagingComponent>(1, false);
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(dmg));

	//create chestComponent and add to the entity
	auto chest = std::make_unique<ChestComponent>(string_code::cFlask_Blue);
	em->add_component_to_entity(id, std::move(chest));
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
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(cha));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
	em->add_component_to_entity(id, std::move(hea));
}

void ComponentFactory::AddBlueFlaskComponents(int id, EntityManager* em) {

	std::map<State, Animation> animations;
	animations.insert({ State::DEFAULT, Engine::LoadAnimation("flask_big_blue.png", 1) });
	animations.at(State::DEFAULT).scale = 2;
	auto ani = std::make_unique<AnimationComponent>(animations, false);
	auto coll = std::make_unique<CollisionComponent>(32, 32, nullptr);
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
}