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

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["HealthComponent"]["current_health"] = current_health;
		j[std::to_string(id)]["HealthComponent"]["max_health"] = max_health;
		j[std::to_string(id)]["HealthComponent"]["time_invulnerable"] = time_invulnerable;
	}
};