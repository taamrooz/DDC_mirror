#pragma once
#include "Component.h"

struct ShootingComponent : Component
{
	enum BulletShape {
		CIRCLE
	};

	ShootingComponent() = default;
	ShootingComponent(int bullet_size, BulletShape bullet_shape = CIRCLE) : 
		bullet_size{ bullet_size }, bullet_shape{ bullet_shape } {}

	int bullet_size{};
	BulletShape bullet_shape{};
};
