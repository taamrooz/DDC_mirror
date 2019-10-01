#pragma once
#include "Component.h"
struct PositionComponent : Component
{
	PositionComponent() = default;
	PositionComponent(int x, int y) : x{ x }, y{ y } {}
	int x{};
	int y{};
};

