#pragma once
#include "Component.h"

struct CollisionComponent : Component
{
	CollisionComponent() = default;
	CollisionComponent(int width, int height) : width{ width }, height{ height } {}
	int width{};
	int height{};
	//Width and height of hitboxes (measured in pixels, so int is fine)
};
