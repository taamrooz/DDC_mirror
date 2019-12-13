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
	float mass = 50;
	int state = Pursuing;
};