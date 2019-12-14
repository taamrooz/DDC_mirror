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
#include "CollectableHandlers.h"
#include "LadderComponent.h"
#include "RoomComponent.h"
#include "RoomSingleton.h"
#include "DamagingComponent.h"
#include "ChestComponent.h"
#include "InventoryComponent.h"
#include "LevelBossComponent.h"
#include "DungeonSingleton.h"
#include "Renderer.h"
#include "CollectableComponent.h"
#include "EnemyComponent.h"

ComponentFactory::ComponentFactory() {
	collision_handlers_;
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

int ComponentFactory::CreateEntity(std::string const& name, int id, Engine::EntityManager<Component>* em, RoomComponent* room) {
	return CreateEntity(Convert(name), id, em, room);
}

int ComponentFactory::CreateEntity(string_code name, int id, Engine::EntityManager<Component>* em, RoomComponent* room)
{
	switch (name) {
	case cPlayer: {
		AddPlayerComponents(id, em, room);
		break;
	}
	case cChest: {
		AddChestComponents(id, em, room);
		break;
	}
	case cladder: {
		AddLadderComponents(id, em, room);
		break;
	}
	case cFlask_Blue: {
		AddBlueFlaskComponents(id, em, room);
		break;
	}
	case cMonster: {
		AddEnemyComponents(id, em, false, room);
		break;
	}
	case cBoss: {
		AddEnemyComponents(id, em, true, room);
		break;
	}
	default: {
		//std::cout << "Error, entity name not found" << std::endl;
	}
	}
	return -1;
}

void ComponentFactory::AddChestComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room) {
	auto coll = std::make_unique<CollisionComponent>(48, 48, ChestCollisionHandler, CollisionHandlerNames::ChestCollisionHandler);
	auto room_component = std::make_unique<RoomComponent>(room->room_name, room->room_index);
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	std::unordered_map<State, std::string> state_to_path;
	std::unordered_map<State, int> state_to_frames;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::unique_ptr<Animation>(Engine::load_animation("Animations/chest_full_open.png", 3))));
	state_to_path.emplace(State::DEFAULT, "Animations/chest_full_open.png");
	state_to_frames.emplace(State::DEFAULT, 3);
	animations.at(State::DEFAULT)->pause = true;
	animations.at(State::DEFAULT)->scale = 3;
	animations.at(State::DEFAULT)->loop = false;
	auto ani = std::make_unique<AnimationComponent>(animations, state_to_path, state_to_frames);
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
    em->add_component_to_entity(id, std::move(room_component));

	//create chestComponent and add to the entity
	auto chest = std::make_unique<ChestComponent>(cFlask_Blue);
	em->add_component_to_entity(id, std::move(chest));
}

void ComponentFactory::AddPlayerComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room) {
	auto hea = std::make_unique<HealthComponent>(5, 5);
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	std::unordered_map<State, std::string> state_to_path;
	std::unordered_map<State, int> state_to_frames;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::unique_ptr<Animation>(Engine::load_animation("Animations/wizard_m_idle.png", 4)) ));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::RUN, std::unique_ptr<Animation>(Engine::load_animation("Animations/wizard_m_run.png", 4) )));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::HIT, std::unique_ptr<Animation>(Engine::load_animation("Animations/wizard_m_hit.png", 1) )));
	state_to_path.emplace(State::DEFAULT, "Animations/wizard_m_idle.png");
	state_to_path.emplace(State::RUN, "Animations/wizard_m_run.png");
	state_to_path.emplace(State::HIT, "Animations/wizard_m_hit.png");
	state_to_frames.emplace(State::DEFAULT, 4);
	state_to_frames.emplace(State::RUN, 4);
	state_to_frames.emplace(State::HIT, 1);
	animations.at(State::DEFAULT)->scale = 3;
	animations.at(State::RUN)->scale = 3;
	animations.at(State::HIT)->scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations, state_to_path, state_to_frames);
	auto cha = std::make_unique<CharacterComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 63, PlayerCollisionHandler, CollisionHandlerNames::PlayerCollisionHandler);
	auto room_comp = std::make_unique<RoomComponent>(room->room_name, room->room_index);
	auto inv = std::make_unique<InventoryComponent>();
	em->add_component_to_entity(id, std::move(hea));
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(cha));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
	em->add_component_to_entity(id, std::move(room_comp));
	em->add_component_to_entity(id, std::move(inv));
}

void ComponentFactory::AddLadderComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room) {
	auto ladder = std::make_unique<LadderComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 48, PlayerCollisionHandler, CollisionHandlerNames::PlayerCollisionHandler);
	auto room_comp = std::make_unique<RoomComponent>(room->room_name, room->room_index);
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(ladder));
	em->add_component_to_entity(id, std::move(room_comp));
}

void ComponentFactory::AddEnemyComponents(int id, Engine::EntityManager<Component>* em, bool level_boss, RoomComponent* room) {
	auto hea = std::make_unique<HealthComponent>(4, 5);
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	auto emc = std::make_unique<EnemyComponent>();
	auto room_comp = std::make_unique<RoomComponent>(room->room_name, room->room_index);
	auto damage = std::make_unique<DamagingComponent>(1);
	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	std::unordered_map<State, std::string> state_to_path;
	std::unordered_map<State, int> state_to_frames;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::unique_ptr<Animation>(Engine::load_animation("Animations/chort_idle.png", 4)) ));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::RUN, std::unique_ptr<Animation>(Engine::load_animation("Animations/chort_run.png", 4) )));
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::HIT, std::unique_ptr<Animation>(Engine::load_animation("Animations/chort_hit.png", 1) )));
	state_to_path.emplace(State::DEFAULT, "Animations/chort_idle.png");
	state_to_path.emplace(State::RUN, "Animations/chort_run.png");
	state_to_path.emplace(State::HIT, "Animations/chort_hit.png");
	state_to_frames.emplace(State::DEFAULT, 4);
	state_to_frames.emplace(State::RUN, 4);
	state_to_frames.emplace(State::HIT, 1);
	animations.at(State::DEFAULT)->scale = 3;
	animations.at(State::RUN)->scale = 3;
	animations.at(State::HIT)->scale = 3;
	auto ani = std::make_unique<AnimationComponent>(animations, state_to_path, state_to_frames);
	auto coll = std::make_unique<CollisionComponent>(48, 63, EnemyCollisionHandler, CollisionHandlerNames::EnemyCollisionHandler, false);
	em->add_component_to_entity(id, std::move(damage));
	em->add_component_to_entity(id, std::move(room_comp));
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

void ComponentFactory::AddBlueFlaskComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room) {

	std::unordered_map<State, std::unique_ptr<Animation>> animations;
	std::unordered_map<State, std::string> state_to_path;
	std::unordered_map<State, int> state_to_frames;
	animations.emplace(std::make_pair<State, std::unique_ptr<Animation>>(State::DEFAULT, std::unique_ptr<Animation>(Engine::load_animation("flask_big_blue.png", 1))));
	state_to_path.emplace(State::DEFAULT, "flask_big_blue.png");
	state_to_frames.emplace(State::DEFAULT, 1);
	animations.at(State::DEFAULT)->scale = 2;
	auto ani = std::make_unique<AnimationComponent>(animations, state_to_path, state_to_frames);
	auto room_comp = std::make_unique<RoomComponent>(room->room_name, room->room_index);
	auto collisi = std::make_unique<CollisionComponent>(32, 32, ItemCollisionHandler, CollisionHandlerNames::ItemCollisionHandler, false);
	auto collect = std::make_unique<CollectableComponent>(CollectableHandlerNames::BlueFlaskCollectableHandler, BlueFlaskCollectableHandler);
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(collisi));
	em->add_component_to_entity(id, std::move(room_comp));
	em->add_component_to_entity(id, std::move(collect));
}