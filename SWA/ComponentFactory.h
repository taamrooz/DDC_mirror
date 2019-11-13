#pragma once
#include <string>
#include "EntityManager.h"
enum string_code {
	cPlayer,
	cWall,
	cChest,
	cFlask_Blue
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
	void AddPlayerComponents(int, EntityManager*);
	void AddBlueFlaskComponents(int id, EntityManager* em);
	void AddChestComponents(int id, EntityManager* em);
	void AddEnemyComponents(int id, EntityManager* em);
public:
	static ComponentFactory* get_instance();
	int CreateEntity(std::string, int id, EntityManager*);
	int CreateEntity(string_code name, int id, EntityManager*);
};

