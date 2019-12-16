#pragma once
#include "BaseSystem.h"
#include "Core.h"
#include "InventoryComponent.h"

class InventorySystem :
	public BaseSystem
{
public:
	InventorySystem(Engine::EntityManager<Component>* manager);
	void update(double dt) override;
	void select_inventory_item(InventoryComponent* inv, uint32_t entity, int option_number);
};