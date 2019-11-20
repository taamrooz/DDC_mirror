#pragma once
#include "BaseSystem.h"
#include "Core.h"
class InventorySystem :
	public BaseSystem
{
public:
	InventorySystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
};