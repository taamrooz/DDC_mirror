#include "CollectableHandlers.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"

void RemoveCollectable(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component>* manager) {
	// Remove collectable from items list in inventory
	auto inv = manager->get_component<InventoryComponent>(collector);
	for (auto it = inv->items.begin(); it != inv->items.end(); ++it)
	{
		if (*it == collectable) {
			inv->items.erase(it);
			break;
		}
	}
	manager->remove_entity(collectable);
}

void BlueFlaskCollectableHandler(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component>* manager) {
	// Set health to max health
	const auto health = manager->get_component<HealthComponent>(collector);
	health->current_health = health->max_health;

	// Cleanup collectable
	RemoveCollectable(collector, collectable, manager);
}

CollectableHandlers::CollectableHandlers()
{
	name_function_map_.try_emplace(CollectableHandlerNames::BlueFlaskCollectableHandler, BlueFlaskCollectableHandler);
	name_function_map_.try_emplace(CollectableHandlerNames::RemoveCollectable, RemoveCollectable);
}

std::function<void(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component>* manager)>
CollectableHandlers::GetFunction(CollectableHandlerNames name)
{
	auto find_return = name_function_map_.find(name);
	return find_return->second;
}
