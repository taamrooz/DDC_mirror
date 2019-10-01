#pragma once
#include "Component.h"

struct HealthComponent : Component
{
	HealthComponent() = default;
	HealthComponent(int current_health, int max_health) : current_health{ current_health }, max_health{ max_health } {}
	int current_health{};
	int max_health{};
	//Health in integers, can always visualize as half hearts on odd numbers (more efficient)
};