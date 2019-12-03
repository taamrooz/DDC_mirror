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
		j[id]["VelocityComponent"]["dx"] = dx;
		j[id]["VelocityComponent"]["dy"] = dy;
		j[id]["VelocityComponent"]["dropOff"] = dropOff;
	}
};
