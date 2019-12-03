#pragma once
#include "Component.h"
#include <string>

struct LevelBossComponent : Component
{
	LevelBossComponent() = default;

	void ToJson(json& j, int id) override
	{
		j[id]["LevelBossComponent"]["present"] = true;
	}
};