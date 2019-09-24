#pragma once
#include "Component.h"

struct DamagingComponent : Component
{
	DamagingComponent() = default;
	DamagingComponent(int damage_amount, bool remove_entity_on_damage = false) : damage_amount{ damage_amount }, remove_entity_on_damage{ remove_entity_on_damage } {}
	int damage_amount{};
	bool remove_entity_on_damage{};
	//When entity deals damage, remove it from the game. Eg. bullets that do not pierce (default:False)
};