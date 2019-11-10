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
#include "DoorComponent.h"
#include "RoomComponent.h"
#include "RoomSingleton.h"
ComponentFactory::ComponentFactory() {

}

ComponentFactory* ComponentFactory::instance_ = 0;

enum string_code {
	cPlayer,
	cWall,
	cChest,
	cDoor
};

string_code Convert(std::string const& inString) {
	if (inString == "player") return cPlayer;
	if (inString == "wall") return cWall;
	if (inString == "chest") return cChest;
	if (inString == "door") return cDoor;
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
	case cDoor: {
		AddDoorComponents(id, em);
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
	auto ani = std::make_unique<AnimationComponent>("Animations/chest_full_open.png", 3, 3);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	ani.get()->animation.pause = true;
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddPlayerComponents(int id, EntityManager* em) {
	auto hea = std::make_unique<HealthComponent>();
	auto sho = std::make_unique<ShootingComponent>(7, 200);
	auto vel = std::make_unique<VelocityComponent>();
	auto ani = std::make_unique<AnimationComponent>("Animations/wizard_m_run.png", 4, 3);
	auto cha = std::make_unique<CharacterComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 84, PlayerCollisionHandler);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	em->add_component_to_entity(id, std::move(vel));
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(cha));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(sho));
	em->add_component_to_entity(id, std::move(room));
}

void ComponentFactory::AddDoorComponents(int id, EntityManager* em) {
	auto door = std::make_unique<DoorComponent>();
	auto coll = std::make_unique<CollisionComponent>(48, 48, PlayerCollisionHandler);
	auto ani = std::make_unique<AnimationComponent>("Animations/floor_spikes.png", 4, 3);
	auto room = std::make_unique<RoomComponent>(RoomSingleton::get_instance()->room_names[RoomSingleton::get_instance()->current_room_index]);
	ani.get()->animation.pause = true;
	em->add_component_to_entity(id, std::move(ani));
	em->add_component_to_entity(id, std::move(coll));
	em->add_component_to_entity(id, std::move(door));
	em->add_component_to_entity(id, std::move(room));
}