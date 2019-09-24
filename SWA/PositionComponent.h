#pragma once
#include "Component.h"

struct position_component : Component
{
	position_component() = default;
	position_component(int x, int y) : x{ x }, y{ y } {}
	int x{};
	int y{};
	//Position is the position it's sprite will be drawn. (Depends on where the base coordinates are for sprite drawing)
};

