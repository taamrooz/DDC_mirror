#pragma once
#include "Component.h"
struct PositionComponent : Component
{
	PositionComponent() = default;
	PositionComponent(int x, int y) : x{ x }, y{ y } {}
	int x{};
	int y{};

	void ToJson(json& j, int id) override
	{
		j[id]["PositionComponent"]["x"] = x;
		j[id]["PositionComponent"]["y"] = y;
	}
};

