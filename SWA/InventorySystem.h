#pragma once
#include "BaseSystem.h"
#include "Core.h"
class InventorySystem :
	public BaseSystem
{
public:
	InventorySystem(EntityManager* manager);
	void update(double dt) override;
};