#pragma once

#pragma once
#include "Component.h"
#include <functional>
#include "Core.h"

struct CollectableComponent : Component
{
	CollectableComponent() = default;
	CollectableComponent(std::function<void(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component> * manager, Core * core)> handler)
		: utilizeHandler{ std::move(handler) } {}
	std::function<void(uint32_t collector, uint32_t collectable, Engine::EntityManager<Component> * manager, Core * core)> utilizeHandler;
	//Width and height of hitboxes (measured in pixels, so int is fine)
};
