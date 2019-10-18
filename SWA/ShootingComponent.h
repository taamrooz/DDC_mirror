#pragma once
#include "Component.h"

struct ShootingComponent : Component
{
	enum BulletShape {
		CIRCLE
	};

	ShootingComponent() = default;
	ShootingComponent(int bullet_size, Uint32 fire_rate, BulletShape bullet_shape = CIRCLE ) :
		bullet_size{ bullet_size }, bullet_shape{ bullet_shape }, fire_rate{ fire_rate }, last_shot{ 0 } {}

	int bullet_size{};
	BulletShape bullet_shape{};
	Uint32 fire_rate{};
	Uint32 last_shot{};
};
