#include "EntityManager.h"

uint32_t EntityManager::create_entity()
{
	entities_.push_back(++id_);
	return id_;
}

uint32_t EntityManager::create_entity(const std::vector<std::shared_ptr<Component>>& components)
{
	entities_.push_back(++id_);
	for (const auto& component : components)
	{
		add_component_to_entity(id_, component);
	}
	return id_;
}

void EntityManager::add_component_to_entity(uint32_t id, const std::shared_ptr<Component>& comp)
{
	const auto& ref = *comp.get();
	const auto type = typeid(*&ref).name();
	const auto exists = components_by_class_[type].emplace(id, comp);
	if(!exists.second){
		exists.first->second = comp;
	}
}

void EntityManager::remove_entity(uint32_t id)
{
	entities_.erase(entities_.begin() + id);
}
