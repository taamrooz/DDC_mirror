#pragma once
#include "Component.h"

struct VelocityComponent : Component
{
	VelocityComponent() = default;
	VelocityComponent(double dx, double dy, double dropOff = 0.0) : dx{ dx }, dy{ dy }, dropOff{ dropOff } {}
	double dx{};
	double dy{};
	double dropOff{};

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["VelocityComponent"]["dx"] = dx;
		j[std::to_string(id)]["VelocityComponent"]["dy"] = dy;
		j[std::to_string(id)]["VelocityComponent"]["dropOff"] = dropOff;
	}
};
