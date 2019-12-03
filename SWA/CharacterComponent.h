#pragma once
#include "Component.h"

struct CharacterComponent : Component
{
	CharacterComponent() = default;

	void ToJson(json& j, int id) override
	{
		j[id]["CharacterComponent"]["present"] = true;
	}
};

