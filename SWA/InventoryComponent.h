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
		j[id]["InventoryComponent"]["selected"] = selected;
		j[id]["InventoryComponent"]["items"] = items;
	}
};