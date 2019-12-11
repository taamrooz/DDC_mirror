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
	float mass = 30;
	int state = Pursuing;
};