#pragma once
#include "Component.h"
#include <map>
struct InventoryComponent : Component
{
	InventoryComponent() = default;
	std::vector<uint32_t> items{};
	int selected = 1;

	void ToJson(json& j, int id) override
	{
		j[std::to_string(id)]["InventoryComponent"]["selected"] = selected;
		j[std::to_string(id)]["InventoryComponent"]["items"] = items;
	}
};