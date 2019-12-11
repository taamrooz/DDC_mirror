#pragma once
#include <cstdint>
#include "EntityManager.h"
#include "BaseSystem.h"
#include "Core.h"

enum class CollectableHandlerNames
{
	None,
	RemoveCollectable,
	BlueFlaskCollectableHandler
};

void RemoveCollectable(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component>* manager);
void BlueFlaskCollectableHandler(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component>* manager);

class CollectableHandlers
{
private:
	std::unordered_map<CollectableHandlerNames, std::function<void(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component> * manager)>> name_function_map_;
public:
	CollectableHandlers();
	std::function<void(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component> * manager)> GetFunction(CollectableHandlerNames name);
};