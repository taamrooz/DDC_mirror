#pragma once
#include "Component.h"
#include <map>
struct InventoryComponent : Component
{
	InventoryComponent() = default;
	std::vector<uint32_t> items{};
};