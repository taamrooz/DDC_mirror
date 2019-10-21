#pragma once
#include "Component.h"
#include <functional>

struct CollisionComponent : Component
{
	CollisionComponent() = default;
	CollisionComponent(int width, int height, std::function<void(uint32_t entity1, uint32_t entity2, EntityManager* manager)> handler) : width{ width }, height{ height }, collisionHandler{ handler } {}
	int width{};
	int height{};
	std::vector<uint32_t> ignore_;
	std::function<void(uint32_t entity1, uint32_t entity2, EntityManager* manager)> collisionHandler;
	//Width and height of hitboxes (measured in pixels, so int is fine)
};
