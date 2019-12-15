#pragma once
#include "Component.h"
#include "vector2d.h"

struct VelocityComponent : Component
{
	VelocityComponent() = default;
	VelocityComponent(double dx, double dy, double dropOff = 0.0) : dx{ dx }, dy{ dy }, dropOff{ dropOff } {}
	vector2d steer_force = vector2d(0,0);
	double dx{4};
	double dy{8};
	float deceleration = 3;
	double dropOff{};
	float maxSpeed = 10;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["VelocityComponent"]["dx"] = dx;
		j[std::to_string(id)]["VelocityComponent"]["dy"] = dy;
		j[std::to_string(id)]["VelocityComponent"]["dropOff"] = dropOff;
		j[std::to_string(id)]["VelocityComponent"]["deceleration"] = deceleration;
		j[std::to_string(id)]["VelocityComponent"]["maxSpeed"] = maxSpeed;
	}
};
