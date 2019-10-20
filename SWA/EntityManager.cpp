#include "EntityManager.h"

uint32_t EntityManager::create_entity()
{
	entities_.push_back(++id_);
	return id_;
}

uint32_t EntityManager::create_entity(std::vector<Component*>& components)
{
	entities_.push_back(++id_);
	for (auto& component : components)
	{
		add_component_to_entity(id_, std::make_unique<Component>(*component));
	}
	return id_;
}

void EntityManager::add_component_to_entity(const uint32_t id, std::unique_ptr<Component> comp)
{
	const auto& ref = *comp;
	const auto type = typeid(*&ref).hash_code();
	//const auto exists = components_by_class_[type].insert_or_assign(id, std::move(comp));
	components_by_class_[type].insert_or_assign(id, std::move(comp));
}

void EntityManager::remove_entity(const uint32_t id)
{
	entities_.erase(entities_.begin() + id);
}
