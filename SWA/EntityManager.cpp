#include "EntityManager.h"

uint32_t EntityManager::create_entity(const std::vector<component*>& components)
{
	_entities.push_back(_id);
	for (component* component : components)
	{
		add_component_to_entity(_id, *component);
	}
	return _id++;
}

void EntityManager::add_component_to_entity(uint32_t id, component& comp)
{
	const std::string type = typeid(comp).name();
	printf("added %s\n", type.c_str());
	auto exists = _componentsByClassName[type].emplace(id, &comp);
	if(!exists.second){
		_componentsByClassName[type][id] = &comp;
	}
}

void EntityManager::remove_entity(uint32_t id)
{
	_entities.erase(_entities.begin() + id);
}
