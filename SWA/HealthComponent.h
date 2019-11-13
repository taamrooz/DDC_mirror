#pragma once
#include "Component.h"

struct HealthComponent : Component
{
	HealthComponent() = default;
	HealthComponent(int current_health, int max_health, int time_invulnerable = 500) : current_health{ current_health }, max_health{ max_health }, invulnerable_until{ 0 }, time_invulnerable{ time_invulnerable } {}
	int current_health{};
	int max_health{};
	int time_invulnerable{};
	int invulnerable_until{};
	//Health in integers, can always visualize as half hearts on odd numbers (more efficient)
};