#pragma once
#include <string>
#include "EntityManager.h"

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
public:
	static ComponentFactory* get_instance();
	int CreateEntity(std::string, int id, EntityManager*);
};

