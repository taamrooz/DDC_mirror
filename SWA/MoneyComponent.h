#pragma once
#include "Component.h"

struct MoneyComponent : Component
{
	MoneyComponent() = default;
	MoneyComponent(int current_money) : current_money{ current_money } {}
	int current_money{};

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["MoneyComponent"]["current_money"] = current_money;
	}
};
