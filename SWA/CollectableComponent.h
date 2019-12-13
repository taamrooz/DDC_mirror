#pragma once

#pragma once
#include "Component.h"
#include <functional>
#include "Core.h"
#include "CollectableHandlers.h"

struct CollectableComponent : Component
{
	CollectableComponent() = default;
	CollectableComponent(CollectableHandlerNames func_name, std::function<void(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component> * manager)> handler)
		: utilizeHandler{ std::move(handler) }, function_name {func_name} {}

	CollectableHandlerNames function_name;
	std::function<void(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component> * manager)> utilizeHandler;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["CollectableComponent"]["function_name"] = function_name;
	}
};
