#include "EntityManager.h"

uint32_t EntityManager::create_entity(const std::vector<Component*>& components)
{
	_entities.push_back(++_id);
	for (Component* component : components)
	{
		add_component_to_entity(_id, *component);
	}
	return _id;
}

void EntityManager::add_component_to_entity(uint32_t id, Component& comp)
{
	const auto type = typeid(comp).name();
	auto exists = _componentsByClassName[type].emplace(id, &comp);
	if(!exists.second){
		_componentsByClassName[type].at(id) = &comp;
	}
}

void EntityManager::remove_entity(uint32_t id)
{
	_entities.erase(_entities.begin() + id);
}
