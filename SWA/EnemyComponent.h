#pragma once
#include "Component.h"

enum enemyState
{
	Fleeing,
	Pursuing
};

struct EnemyComponent : Component
{
	EnemyComponent() = default;
	EnemyComponent(float mass) : mass{ mass } {};
	float mass = 50;
	int state = Pursuing;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["EnemyComponent"]["mass"] = mass;
		j[std::to_string(id)]["EnemyComponent"]["state"] = state;
	}
};