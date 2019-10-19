#pragma once
#include "BaseSystem.h"
#include "Core.h"

class InputSystem :
	public BaseSystem

{
public:
	InputSystem(EntityManager* manager, Core &core);
	void update(double dt) override;
private:
	Core* core;
};

