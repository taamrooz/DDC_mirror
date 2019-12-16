#pragma once
#include "Component.h"

struct LadderComponent : Component
{
	LadderComponent() = default;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["LadderComponent"]["present"] = true;
	}
};