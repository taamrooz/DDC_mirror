#pragma once
#include "Component.h"

struct ShootingComponent : Component
{
	enum class BulletShape {
		CIRCLE
	};

	ShootingComponent() = default;
	ShootingComponent(int bullet_size, int fire_rate, BulletShape bullet_shape = BulletShape::CIRCLE ) :
		bullet_size{ bullet_size }, bullet_shape{ bullet_shape }, fire_rate{ fire_rate }, last_shot{ 0 } {}

	int bullet_size{};
	BulletShape bullet_shape{};
	int fire_rate{};
	int last_shot{};
};
