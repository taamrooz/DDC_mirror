#pragma once
#include "Component.h"

struct MoneyComponent : Component
{
	MoneyComponent() = default;
	MoneyComponent(int current_money) : current_money{ current_money } {}
	int current_money{};
};
