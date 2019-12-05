#pragma once
#include "Component.h"
#include <functional>
#include "Core.h"
#include "CollisionHandlers.h"

struct CollisionComponent : Component
{
	CollisionComponent() = default;
	CollisionComponent(int width, int height, std::function<void(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core)> handler,HandlerNames function_name ,bool solid = true, int owner = -1)
		: width{ width }, height{ height }, owner{ owner }, collisionHandler{ std::move(handler) }, function_name{function_name}, solid{ solid } {}
	int width{};
	int height{};
	int owner{};
	bool solid{};
	HandlerNames function_name{};
	std::function<void(uint32_t entity1, uint32_t entity2, Engine::EntityManager<Component>* manager, Core* core)> collisionHandler;
	//Width and height of hitboxes (measured in pixels, so int is fine)

	void ToJson(json& j, int id) override
	{
		j[id]["CollisionComponent"]["width"] = width;
		j[id]["CollisionComponent"]["height"] = height;
		j[id]["CollisionComponent"]["owner"] = owner;
		j[id]["CollisionComponent"]["solid"] = solid;
		j[id]["CollisionComponent"]["function_name"] = function_name;
	}
};
