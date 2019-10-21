#pragma once
#include "Component.h"
#include <functional>

struct CollisionComponent : Component
{
	CollisionComponent() = default;
	CollisionComponent(int width, int height, std::function<void(uint32_t entity1, uint32_t entity2, EntityManager * manager)> handler, int owner = -1) : width{ width }, height{ height }, owner{owner}, collisionHandler{ std::move(handler) } {}
	int width{};
	int height{};
	int owner{};
	std::function<void(uint32_t entity1, uint32_t entity2, EntityManager* manager)> collisionHandler;
	//Width and height of hitboxes (measured in pixels, so int is fine)
};
