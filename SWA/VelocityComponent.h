#pragma once
#include "Component.h"

struct VelocityComponent : Component
{
	VelocityComponent() = default;
	VelocityComponent(double dx, double dy) : dx{ dx }, dy{ dy } {}
	double dx{};
	double dy{};
};
