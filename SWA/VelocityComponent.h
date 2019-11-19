#pragma once
#include "Component.h"

struct VelocityComponent : Component
{
	VelocityComponent() = default;
	VelocityComponent(double dx, double dy, double dropOff = 0.0) : dx{ dx }, dy{ dy }, dropOff{ dropOff } {}
	double dx{};
	double dy{};
	double dropOff{};
};
