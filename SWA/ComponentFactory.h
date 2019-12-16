#pragma once
#include <string>
#include "EntityManager.h"
#include "CollisionHandlers.h"

enum string_code {
	cPlayer,
	cWall,
	cChest,
	cMonster,
	cladder,
	cFlask_Blue,
	cBoss,
	cChort,
	cImp,
	cZombie,
	cOgre,
	cBigDemon
};
class ComponentFactory
{
private:
	ComponentFactory();
	ComponentFactory(const ComponentFactory& entityFactory) = delete; // Copy constructor
	ComponentFactory(const ComponentFactory&& entityFactory) = delete;  // Move constructor
	ComponentFactory& operator=(const ComponentFactory& entityFactory) = delete; // Assignment operator
	ComponentFactory& operator=(const ComponentFactory&& entityFactory) = delete; // Move operator
	static ComponentFactory* instance_;
	CollisionHandlers collision_handlers_;
	void AddPlayerComponents(int, Engine::EntityManager<Component>*, RoomComponent* room);
	void AddChestComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room);
	void AddBlueFlaskComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room);
	void AddLadderComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room);
	void AddChortComponents(int id, Engine::EntityManager<Component>*, RoomComponent* room);
	void AddZombieComponents(int id, Engine::EntityManager<Component>*, bool level_boss, RoomComponent* room);
	void AddImpComponents(int id, Engine::EntityManager<Component>* em, RoomComponent* room);
	void AddOgreComponents(int id, Engine::EntityManager<Component>*, bool level_boss, RoomComponent* room);
	void AddBigDemonComponents(int id, Engine::EntityManager<Component>* em, bool level_boss, RoomComponent* room);
public:
	static ComponentFactory* get_instance();
	int CreateEntity(std::string const& name, int id, Engine::EntityManager<Component>*, RoomComponent* room);
	int CreateEntity(string_code name, int id, Engine::EntityManager<Component>* em, RoomComponent* room);
};

