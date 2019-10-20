#pragma once
#include "Component.h"
#include <functional>

struct CollisionComponent : Component
{
	CollisionComponent() = default;
	CollisionComponent(int width, int height, std::function<void(uint32_t entity1, uint32_t entity2)> handler) : width{ width }, height{ height }, collisionHandler{ handler } {}
	int width{};
	int height{};
	std::function<void(uint32_t entity1, uint32_t entity2)> collisionHandler;
	//Width and height of hitboxes (measured in pixels, so int is fine)
};
