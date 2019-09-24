#pragma once
#include "Component.h"

struct velocity_component : Component
{
	velocity_component() = default;
	velocity_component(double dx, double dy) : dx{ dx }, dy{ dy } {}
	double dx{};
	double dy{};
	//Could add a speed component and change the dx/dy to 4 directional booleans (up/down/left/right) depends on what's easier to implement
};
