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
	cBoss
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
	void AddPlayerComponents(int, Engine::EntityManager<Component>*);
	void AddChestComponents(int id, Engine::EntityManager<Component>* em);
	void AddBlueFlaskComponents(int id, Engine::EntityManager<Component>* em);
	void AddLadderComponents(int id, Engine::EntityManager<Component>* em);
	void AddEnemyComponents(int id, Engine::EntityManager<Component>*, bool level_boss);
public:
	static ComponentFactory* get_instance();
	int CreateEntity(std::string const& name, int id, Engine::EntityManager<Component>*);
	int CreateEntity(string_code name, int id, Engine::EntityManager<Component>* em);
};

