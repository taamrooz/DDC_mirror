#pragma once
#include "Component.h"
#include "vector2d.h"

struct VelocityComponent : Component
{
	VelocityComponent() = default;
	VelocityComponent(double dx, double dy, double dropOff = 0.0) : dx{ dx }, dy{ dy }, dropOff{ dropOff } {}
	vector2d steer_force = vector2d(0,0);
	double dx{0};
	double dy{0};
	float deaceleration = 3;
	double dropOff{};
	float maxSpeed = 10;
};